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
3. Copy `platformio_override.example.ini` to `platformio_override.ini`.
   - You can get your SPAD.neXt authentication key via their Discord server.  See their website and docs for details.
   - Device GUIDS are at your choosing.  Ensure it is surrounded with curly braces e.g. `{GUID}`.
4. Connect an Arduino Mega 2560.
5. If needed, adjust the serial port in your PlatformIO configuration or let PlatformIO auto-detect.

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

## Scripts and Tasks

No custom scripts are included. Use PlatformIO tasks/targets:

- `pio run` build
- `pio run -t upload` compile and upload
- `pio device monitor` serial monitor
- `pio run -t clean` clean build artifacts

In IDEs, these appear under PlatformIO: Build, Upload, Clean, Monitor.

## License

This project is licensed under the GNU General Public License v3.0—see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- LT McComb and the crew at [flightsimdiy.com](https://flightsimdiy.com) for their hardware!
- c0nnex for [SPAD.neXt](https://www.spadnext.com/)
