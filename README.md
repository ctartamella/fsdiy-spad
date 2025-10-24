# FSDIY Firmware for SPAD.neXt

This repository contains Arduino firmware for custom flight-sim hardware panels that integrate with SPAD.neXt.
The codebase supports multiple device variants selected at build time via PlatformIO environments:

- G1000 NXi PFD1
- G1000 NXi MFD
- G1000 NXi PFD2
- GMA1347 Audio Panel
- GCU378 Autopilot

Device selection is done with preprocessor macros defined per environment in platformio.ini and resolved at runtime by Singletons.cpp.

The firmware is designed to be fairly customizable and can be easily extended really to any Arduino based device.

This firmware is not connected to or affiliated with the flightsimdiy.com project.  This software is provided under
"I made this for myself and thought people might find it useful" terms.

## Setup

1. Install PlatformIO:
   - VS Code: install the PlatformIO IDE extension
   - CLI: pip install -U platformio
2. Clone this repository.
3. Connect an Arduino Mega 2560.
4. If needed, adjust the serial port in your PlatformIO configuration or let PlatformIO auto-detect.

## Build, Upload, and Monitor

This project defines multiple environments in platformio.ini. Pick one of the following examples (replace <port> if auto-detection fails):

- Build only:
  - `pio run -e {environment-name}`
- Upload firmware:
  - `pio run -e {environment-name} -t upload`

Available environments include:

- `g1000nxi_pfd1` (Designed to be used with MOSFET control of the backlight as outlined in the documentation for the package) and in (TODO) premade SPAD profiles will be the pilot PFD.
- `g1000nxi_mfd`
- `g1000nxi_pfd2` (No backlight control, right pilot PFD.)
- `gma1347`
- `gcu378`

## Environments and Configuration

platformio.ini defines common build flags and per-device flags:

Common flags (applied to all environments):

- SPAD_AUTHKEY
- SPAD_DEVICEVERSION

Per-environment flags:

- FSDIY_G1000 / FSDIY_G1000_PFD1 | FSDIY_G1000_MFD | FSDIY_G1000_PFD2
- FSDIY_GMA1347
- SPAD_DEVICEID
- SPAD_DEVICENAME

These are preprocessor macros, not OS environment variables. Edit platformio.ini to change them. Example snippet:

[env:g1000nxi_pfd1]
build_flags =
    ${env.build_flags}
    -D FSDIY_G1000
    -D FSDIY_G1000_PFD1
    -D SPAD_DEVICEID="\"{63C4EC7B-DF0C-46EA-BEB8-EBBE3255B4BD}\""
    -D SPAD_DEVICENAME="\"FSDIY G1000 NXi PFD1\""

Device selection

- See src/Singletons.cpp: it constructs the appropriate device class based on the defined macros (G1000Nxi or Gma1347).

## Scripts and Tasks

No custom scripts are included. Use PlatformIO tasks/targets:

- `pio run` build
- `pio run -t upload` compile and upload
- `pio device monitor` serial monitor
- `pio run -t clean` clean build artifacts

In IDEs, these appear under PlatformIO: Build, Upload, Clean, Monitor.

## Runtime Behavior

- src/main.cpp initializes Serial and Serial1 at 115200, sets up CmdMessenger callbacks, and delegates to the selected SpadDevice implementation.
- The code interfaces with SPAD.neXt commands/events via CmdMessenger. Unknown commands and supported features (LEDs, backlights) are handled conditionally depending on the device.

## Configuration and Environment Variables

- There are no OS environment variables required by the firmware.
- Configuration is performed via preprocessor macros in platformio.ini as described above.
- TODO: Document hardware pin assignments and wiring per device variant.

## Tests

No automated tests are present in this repository.

- TODO: Add unit tests (e.g., Unity/ArduinoUnit) for protocol parsing and device logic where feasible.

## License

No license file detected.

- TODO: Add a LICENSE file to clarify usage and distribution terms.

## Acknowledgements

- CmdMessenger library by Thijs Elenbaas
- Additional libraries credited via PlatformIO lib_deps
