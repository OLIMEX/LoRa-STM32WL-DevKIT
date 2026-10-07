#!/bin/bash

ERASE_NVM=0

for arg in "$@"; do
  case "$arg" in
    --erase-nvm) ERASE_NVM=1 ;;
    *) echo "Unknown option: $arg"; echo "Usage: $0 [--erase-nvm]"; exit 1 ;;
  esac
done

OPENOCD_IFACE='-f interface/cmsis-dap.cfg -c "cmsis_dap_vid_pid 0x15ba 0x0044" -c "transport select swd" -c "adapter speed 1000" -f target/stm32wlx.cfg'

# Unlock + full erase + program
openocd -f interface/cmsis-dap.cfg -f target/stm32wlx.cfg \
  -c "init; reset halt; stm32wlx unlock 0; flash erase_sector 0 0x0 last; reset halt; shutdown" && \
openocd -f "interface/cmsis-dap.cfg" -c "cmsis_dap_vid_pid 0x15ba 0x0044" \
  -c "transport select swd" -c "adapter speed 1000" -f "target/stm32wlx.cfg" \
  -c "program Release/LoRa-WAN-915MHz.elf verify reset exit" || exit 1

# Optionally erase NVM (LoRaWAN context) after flashing
if [ "$ERASE_NVM" -eq 1 ]; then
  echo "Erasing LoRaWAN NVM at 0x0803F000 (4KB)..."
  openocd -f "interface/cmsis-dap.cfg" -c "cmsis_dap_vid_pid 0x15ba 0x0044" \
    -c "transport select swd" -c "adapter speed 1000" -f "target/stm32wlx.cfg" \
    -c "init; reset halt; flash erase_address 0x0803F000 0x1000; reset; shutdown" || exit 1
  echo "NVM erased — device will factory-reset LoRaWAN credentials on next boot."
fi

sudo picocom -b 115200 /dev/ttyACM0
