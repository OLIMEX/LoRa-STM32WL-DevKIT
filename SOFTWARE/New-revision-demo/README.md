# LoRa-STM32WL-DevKIT LoRaWAN demos for BB-STM32WL revision D1

This folder contains two LoRaWAN end-device demo projects for the Olimex
**LoRa-STM32WL-DevKIT**. They are intended **only for boards fitted with a
BB-STM32WL module marked hardware revision D1**.

For BB-STM32WL revision C or older, use the legacy project and instructions in
[`../Old-revision-demo`](../Old-revision-demo/) instead.

> [!IMPORTANT]
> These projects contain the RF front-end control required by BB-STM32WL
> revision D1. Do not use the binaries on an older BB-STM32WL revision. Check
> the revision marking printed on the module before building or programming.

Always connect an antenna suitable for the selected frequency band before
powering the radio or running the demo.

## Included projects

| Project | LoRaWAN region | Intended use | Demo uplink |
| --- | --- | --- | --- |
| [`LoRaWAN/868/LoRaWAN-868MHz`](LoRaWAN/868/LoRaWAN-868MHz/) | EU868 | Europe and other locations where the EU868 regional parameters are permitted | Unconfirmed message on FPort 2 every 10 seconds; 3-byte temperature/battery test payload |
| [`LoRaWAN/915/LoRa-WAN-915MHz`](LoRaWAN/915/LoRa-WAN-915MHz/) | US915 | North America and other locations where the US915 regional parameters are permitted | Confirmed message on FPort 2 every 10 seconds; 3-byte temperature/battery test payload; configured for US915 sub-band 2 |

The demo payload in both projects is encoded as follows:

| Byte(s) | Value |
| --- | --- |
| 0-1 | Signed 16-bit temperature in degrees Celsius, most-significant byte first |
| 2 | Firmware battery scale: `0` is below the configured minimum, `1` is very low, and `254` is full |

Both applications use OTAA, LoRaWAN Class A, the STM32WLE5CCU6 internal
sub-GHz radio, and UART diagnostic output at 115200 baud. The D1 RF switch is
controlled through `FE_CTRL1` on PC13 and `FE_CTRL2` on PB8.

The selected radio band must be legal in the country of operation and must
match both the gateway and the device profile in the LoRaWAN network server.
The customer is responsible for observing local radio regulations, including
duty-cycle and transmit-power limits.

## Software to use

### Editing and building

Use the Eclipse-based [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html).
The repository already contains the STM32 HAL, CMSIS, LoRaWAN middleware, and
the Eclipse project metadata, so a separate middleware download is not needed
for a normal build.

The `.ioc` files were generated with:

- STM32CubeMX 6.17.0
- STM32CubeWL firmware package 1.5.0
- GCC / STM32CubeIDE project format

A newer STM32CubeIDE may offer to migrate the project. Back up local changes
before accepting migration. If pin or middleware code must be regenerated,
use STM32CubeMX 6.17.0 with STM32CubeWL 1.5.0 to minimize generated-code
differences.

### Programming the board

Use [OpenOCD](https://openocd.org/) with the board's built-in CMSIS-DAP probe.
The supplied `flash.sh` scripts use USB VID:PID `15ba:0044`, SWD at 1 MHz, and
the OpenOCD `stm32wlx` target.

STM32CubeIDE can build the firmware, but its normal ST-LINK programming flow is
not the programming method for the onboard CMSIS-DAP probe. STM32CubeProgrammer
is also not required for the supplied onboard-probe workflow.

On Linux, the helper script additionally uses `picocom` for the serial log.
On Windows, use OpenOCD to program the ELF file and any serial-terminal program
(for example PuTTY or Tera Term) to view the virtual COM port.

### LoRaWAN service

A compatible LoRaWAN gateway and network server are required. The Things Stack,
ChirpStack, or another standards-compatible LoRaWAN network server can be used.
Create the end device as an OTAA device and select the same regional frequency
plan as the firmware.

## Configure the OTAA credentials

Each physical device must have unique production credentials. Edit
`LoRaWAN/App/se-identity.h` in the selected project and set:

- `LORAWAN_DEVICE_EUI` (DevEUI). If it remains all zero, the firmware derives a
  value from the STM32 unique device information; register the resulting value
  shown in the serial log.
- `LORAWAN_JOIN_EUI` (called AppEUI by LoRaWAN 1.0.x network servers).
- `LORAWAN_GEN_APP_KEY` (AppKey for LoRaWAN 1.0.x).
- `LORAWAN_APP_KEY` (NwkKey for LoRaWAN 1.1.x).

The values included in the source are examples and must not be reused for a
deployed device. Keep production root keys private and do not commit them to a
public repository.

Credential files:

- EU868: `LoRaWAN/868/LoRaWAN-868MHz/LoRaWAN/App/se-identity.h`
- US915: `LoRaWAN/915/LoRa-WAN-915MHz/LoRaWAN/App/se-identity.h`

## Build

### EU868

1. In STM32CubeIDE, select **File > Import > General > Existing Projects into
   Workspace**.
2. Select `LoRaWAN/868/LoRaWAN-868MHz` as the project directory.
3. Select the **Release** configuration and build the `LoRaWAN-868MHz` project.
4. The expected image is
   `LoRaWAN/868/LoRaWAN-868MHz/Release/LoRaWAN-868MHz.elf`.

The outer `LoRaWAN/868` directory also contains an exported source/build copy
and Eclipse metadata. Use the self-contained project path above for a clean
import, and do not import both copies into the same STM32CubeIDE workspace
because they use the same Eclipse project name.

### US915

1. In STM32CubeIDE, select **File > Import > General > Existing Projects into
   Workspace**.
2. Select `LoRaWAN/915/LoRa-WAN-915MHz` as the project directory.
3. Select the **Release** configuration and build the `LoRa-WAN-915MHz` project.
4. The expected image is
   `LoRaWAN/915/LoRa-WAN-915MHz/Release/LoRa-WAN-915MHz.elf`.

## Program and monitor on Linux

Install OpenOCD and picocom, connect the DevKIT's USB port, and run the helper
from the selected project directory:

```sh
# EU868
cd LoRaWAN/868/LoRaWAN-868MHz
./flash.sh

# US915
cd LoRaWAN/915/LoRa-WAN-915MHz
./flash.sh
```

The script erases the target, programs and verifies the Release ELF, resets the
board, and opens `/dev/ttyACM0` at 115200 baud. If the serial port has a
different name, run OpenOCD manually and open the correct port in picocom.

For either project, pass `--erase-nvm` when changing credentials or when a
stored network session prevents a clean join:

```sh
./flash.sh --erase-nvm
```

## Program manually with OpenOCD

Run from the directory that contains the chosen `Release` folder:

```sh
openocd -f interface/cmsis-dap.cfg \
  -c "cmsis_dap_vid_pid 0x15ba 0x0044" \
  -c "transport select swd" \
  -c "adapter speed 1000" \
  -f target/stm32wlx.cfg \
  -c "program Release/PROJECT_NAME.elf verify reset exit"
```

Replace `PROJECT_NAME.elf` with `LoRaWAN-868MHz.elf` or
`LoRa-WAN-915MHz.elf`. The same command structure can be used from Windows
PowerShell or Command Prompt if `openocd` is on `PATH`; omit the Unix line
continuation characters as appropriate.

## Serial output and first join

Open the board's virtual COM port with these settings:

- 115200 baud
- 8 data bits
- no parity
- 1 stop bit
- no flow control

After reset, the firmware prints its LoRaWAN identity and join status. Confirm
that the DevEUI printed by the board is the DevEUI registered in the network
server. A successful OTAA exchange is followed by `JOINED`/`[DONE]` and then
periodic uplink messages.

If the device does not join:

1. Verify that the module is BB-STM32WL revision D1.
2. Verify the antenna and the selected EU868 or US915 project.
3. Check that DevEUI, JoinEUI/AppEUI, AppKey, and NwkKey match the network
   server exactly, including byte order.
4. For US915, configure the gateway/network frequency plan for sub-band 2.
5. Erase the saved LoRaWAN context after changing credentials, then reset and
   try again.
6. Check the 115200-baud serial log for `JOINFAIL`, radio, or programming
   errors.

## Main configuration files

| Setting | File in each project |
| --- | --- |
| OTAA identifiers and keys | `LoRaWAN/App/se-identity.h` |
| Active region, uplink interval, and FPort | `LoRaWAN/App/lora_app.h` |
| Join, transmit, receive, and demo-payload logic | `LoRaWAN/App/lora_app.c` |
| Compiled regional support | `LoRaWAN/Target/lorawan_conf.h` |
| D1 RF front-end switching | `LoRaWAN/Target/radio_board_if.c` and `.h` |
| Clock, GPIO, USART, and MCU configuration | project `.ioc` file |

## References

- [LoRa-STM32WL-DevKIT product page](https://www.olimex.com/Products/IoT/LoRa/LoRa-STM32WL-DevKit/open-source-hardware)
- [Olimex LoRa-STM32WL-DevKIT repository](https://github.com/OLIMEX/LoRa-STM32WL-DevKIT)
- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
- [OpenOCD](https://openocd.org/)
