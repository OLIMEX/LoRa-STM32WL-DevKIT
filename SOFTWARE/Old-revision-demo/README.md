# LoRa-STM32WL-DevKIT demo for BB-STM32WL revision C and older

This folder contains the legacy EU868 LoRaWAN sensor demo for the Olimex
**LoRa-STM32WL-DevKIT** when it is fitted with a **BB-STM32WL hardware revision
C or older** module.

> [!IMPORTANT]
> Do not program this firmware into a BB-STM32WL revision D1 module. Revision
> D1 uses the newer projects and RF front-end handling in
> [`../New-revision-demo`](../New-revision-demo/). Check the revision marking
> printed on the module before programming.

Always connect a suitable 868 MHz antenna before powering the radio or running
the demo.

## What is included

| Path | Purpose |
| --- | --- |
| [`BB-STM32WLE-WAN`](BB-STM32WLE-WAN/) | STM32CubeIDE end-device project for the STM32WLE5CCU6 |
| [`cmsis-dap`](cmsis-dap/) | Source and build files for the STM32L052-based onboard CMSIS-DAP probe; not required for normal end-device development |
| `flashit` | Example OpenOCD command for programming through the onboard CMSIS-DAP probe |

The end-device project is configured for:

- EU868
- LoRaWAN Class A
- OTAA activation
- adaptive data rate enabled
- unconfirmed uplinks
- AHT20 temperature/humidity sensor by default
- IIS2MDC three-axis magnetometer
- ambient-light and supply-voltage ADC readings
- USART1 diagnostic output at 115200 baud

The sensor uplink is attempted approximately every 10 seconds. It contains a
14-byte example payload assembled in `Core/Src/main.c` from supply-voltage,
temperature, humidity, light, pressure, and three magnetometer values. Treat
this as demonstration encoding: review the units and scaling in `main.c` and
define a decoder that matches your application before deployment.

The selected EU868 band must be legal in the country of operation and must
match the gateway and the device profile in the LoRaWAN network server. The
customer is responsible for local duty-cycle and transmit-power requirements.

## Software to use

### Editing and building

For the most reproducible build, use the Eclipse-based
[STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) 1.14.0.
The project already includes the `-fcommon` compiler option required by newer
GCC-based STM32CubeIDE versions. A newer IDE can normally import it, but may
offer to migrate the project; back up local changes before accepting migration.

The project configuration was generated with:

- STM32CubeIDE 1.14.0
- STM32CubeMX 6.3.0
- STM32CubeWL firmware package 1.1.0
- GCC toolchain / STM32CubeIDE project format

The repository contains its HAL, CMSIS, LoRaWAN middleware, and sensor drivers,
so no separate firmware package is required for an ordinary build. Use the
listed CubeMX and CubeWL versions if the `.ioc` file must be regenerated, since
regeneration with a newer package can substantially change the legacy source.

### Programming and serial monitor

Use [OpenOCD](https://openocd.org/) with the DevKIT's built-in CMSIS-DAP probe.
The probe uses USB VID:PID `15ba:0044`. STM32CubeIDE is used to build the ELF,
but its normal ST-LINK programming flow is not the programming method for this
onboard probe.

Use picocom, PuTTY, Tera Term, or another serial-terminal program for the log:

- 115200 baud
- 8 data bits
- no parity
- 1 stop bit
- no flow control

### LoRaWAN service

A compatible EU868 LoRaWAN gateway and network server are required. The Things
Stack, ChirpStack, or another standards-compatible LoRaWAN network server can
be used. Register the device for OTAA and select an EU868 frequency plan.

## Configure the hardware sensor variant

The project defaults to AHT20. In
`BB-STM32WLE-WAN/Core/Src/main.c`, the following line is commented:

```c
//#define BMP280
```

- Leave it commented for a board populated with AHT20.
- Uncomment it for a board populated with BMP280/BME280, then rebuild.

Check the sensor fitted to the DevKIT rather than assuming it only from the
BB-STM32WL module revision.

## Configure OTAA credentials

Edit:

`BB-STM32WLE-WAN/LoRaWAN/App/se-identity.h`

Set unique values supplied by the LoRaWAN network-server registration:

- `LORAWAN_DEVICE_EUI` (DevEUI)
- `LORAWAN_JOIN_EUI` (AppEUI in LoRaWAN 1.0.x terminology)
- `LORAWAN_APP_KEY` (application root key)
- `LORAWAN_NWK_KEY` (network root key for LoRaWAN 1.1.x)

`STATIC_DEVICE_EUI` is set to `1`, so the all-zero DevEUI in the supplied source
is used literally; this legacy project does not automatically replace it with
an MCU-derived value. Replace all placeholder identifiers and keys before
attempting to join. Keep production root keys private and do not commit them to
a public repository.

## Select a valid application port

The current source leaves this assignment commented in `Core/Src/main.c`:

```c
//AppData.Port = SENSORS_PAYLOAD_APP_PORT;
```

Before using the sensor uplink, define an application port in the range 1-223
and assign it to `AppData.Port`, for example:

```c
AppData.Port = 2;
```

FPort 0 is reserved for LoRaWAN MAC commands and must not carry the 14-byte
application payload.

## Build

1. Start STM32CubeIDE.
2. Select **File > Import > General > Existing Projects into Workspace**.
3. Select `Old-revision-demo/BB-STM32WLE-WAN` as the project directory.
4. Select the **Release** build configuration.
5. Clean and build the `BB-STM32WLE-WAN` project.

The expected output is:

`BB-STM32WLE-WAN/Release/BB-STM32WLE-WAN.elf`

No prebuilt end-device ELF is included in this folder, so build the project
before programming it.

## Program with OpenOCD

From `Old-revision-demo/BB-STM32WLE-WAN`, run:

```sh
openocd -f interface/cmsis-dap.cfg \
  -c "cmsis_dap_vid_pid 0x15ba 0x0044" \
  -c "transport select swd" \
  -c "adapter speed 4000" \
  -f target/stm32wlx.cfg \
  -c "program Release/BB-STM32WLE-WAN.elf verify reset exit"
```

The `flashit` file contains the original abbreviated example. The command above
adds the Release path, verification, reset, and clean OpenOCD exit.

OpenOCD works on Linux, Windows, and macOS. On Windows, place `openocd` on
`PATH` and enter the command on one line or adapt the line continuations for
PowerShell.

## First run

1. Connect the antenna and the DevKIT USB cable.
2. Open the virtual COM port at 115200 8-N-1.
3. Reset the board.
4. Confirm that the AHT20 or BMP280/BME280 sensor and IIS2MDC magnetometer are
   detected in the serial output.
5. Check the OTAA result for `JOINED` or `JOIN FAILED`.
6. After a successful join, monitor `SEND REQUEST` and the uplink counter.

If the device does not join, verify the hardware revision, antenna, EU868
frequency plan, DevEUI, JoinEUI/AppEUI, AppKey, and NwkKey. Pay attention to
byte order when copying identifiers and keys from the network server.

## Onboard CMSIS-DAP firmware

The `cmsis-dap` directory is the firmware project for the DevKIT's separate
STM32L052 debugger/interface microcontroller. It is not LoRaWAN application
code and does not need to be built or programmed for normal use. Reprogramming
the interface MCU incorrectly can disable onboard programming and the virtual
COM port; only use that directory when intentionally restoring or developing
the debugger firmware.

## Main configuration files

| Setting | File |
| --- | --- |
| Hardware pin, clock, peripheral, and middleware setup | `BB-STM32WLE-WAN/BB-STM32WLE-WAN.ioc` |
| Sensor selection, sampling, payload, and send interval | `BB-STM32WLE-WAN/Core/Src/main.c` |
| OTAA identifiers and keys | `BB-STM32WLE-WAN/LoRaWAN/App/se-identity.h` |
| Region, class, activation, ADR, and confirmed/unconfirmed mode | `BB-STM32WLE-WAN/LoRaWAN/App/lora_app.h` |
| Join, receive, and transmit callbacks | `BB-STM32WLE-WAN/LoRaWAN/App/lora_app.c` |
| Legacy radio-board support | `BB-STM32WLE-WAN/LoRaWAN/Target/` |

## References

- [LoRa-STM32WL-DevKIT product page](https://www.olimex.com/Products/IoT/LoRa/LoRa-STM32WL-DevKit/open-source-hardware)
- [Olimex LoRa-STM32WL-DevKIT repository](https://github.com/OLIMEX/LoRa-STM32WL-DevKIT)
- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
- [OpenOCD](https://openocd.org/)
