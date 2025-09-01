# NHD-EVE-TFT Demo

This repository is a **tech demo** showcasing the use of the **Newhaven Display 7" EVE TFT** with the **Gameduino 2 library**. It demonstrates how to drive and render graphics on the FT8xx Embedded Video Engine (EVE) using a microcontroller with PlatformIO.

## Features
- Example setup for the **NHD-7.0-800480FT-CSXN-CTP** (7" Newhaven EVE TFT display).  
- Uses the **Gameduino 2** library for high-level graphics commands.  
- Modular code structure with `include/`, `src/`, and `test/` directories.  
- Ready-to-build with **PlatformIO**.  

## Hardware
- **Display**: Newhaven Display 7" EVE TFT (FT8xx controller).  
- **MCU**: Any PlatformIO-supported microcontroller with SPI (tested with Arduino-compatible boards).  
- **Interface**: SPI + additional control pins (CS, PD, INT).  

## Software
- [PlatformIO](https://platformio.org/) build system.  
- [Gameduino 2 library](https://github.com/jamesbowman/gd2-lib) for graphics.  

## Getting Started
1. Clone this repository:
   ```bash
   git clone https://github.com/JoshLChan/NHD-EVE-TFT.git
   cd NHD-EVE-TFT
2. Open the project in PlatformIO.
3. Connect your display to the MCU (see datasheet for pinout).
4. Build and upload the firmware:
   ```bash
   pio run --target upload
5. Reset your board — the demo should run on the TFT display.
