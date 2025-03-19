# Bare Metal OS for Raspberry Pi 4

## Overview
This project is a bare-metal operating system for the Raspberry Pi 4, written in C and Assembly. It is built using CMake and cross-compiled with the `aarch64-none-elf-gcc` toolchain.

## Features
- Runs directly on the Raspberry Pi 4 with no underlying OS
- UART communication support
- Custom command-line interface with history and autocomplete
- Various built-in commands for system interaction
- Minimal bootloader written in Assembly

## Requirements
### Hardware:
- Raspberry Pi 4
- microSD card
- UART-to-USB adapter (for serial debugging)

### Software:
- CMake 3.27+
- AArch64 cross-compiler (`aarch64-none-elf-gcc`)
- QEMU (for emulation)
- Make

## Project Structure
```
project_root/
├── src/            # Source code
│   ├── error/      # Error handling
│   ├── string/     # String manipulation functions
│   ├── cmd/        # Command-line interface
│   ├── uart/       # UART communication
│   ├── kernel.c    # Main kernel logic
│   ├── mbox.c      # Mailbox communication
├── include/        # Header files
├── link/           # Linker scripts and boot assembly
│   ├── boot.S      # Assembly bootloader
│   ├── link.ld     # Linker script
├── CMakeLists.txt  # Build configuration
└── README.md       # Project documentation
```

## Setup and Compilation
1. Install the required cross-compilation tools:
   ```sh
   sudo apt install gcc-aarch64-none-elf qemu-system-aarch64 cmake make
   ```
2. Clone the repository:
   ```sh
   git clone https://github.com/your-repo/baremetal-raspberrypi.git
   cd baremetal-raspberrypi
   ```
3. Create a build directory and compile the project:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
4. Convert the kernel to a bootable image:
   ```sh
   aarch64-none-elf-objcopy -O binary kernel.elf kernel8.img
   ```
5. Copy `kernel8.img` to the root of a FAT32-formatted microSD card.
6. Insert the SD card into the Raspberry Pi 4 and power it on.

## Running in QEMU
To test the kernel in QEMU:
```sh
qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio
```

## Configuration
### `CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.27)
project(asm2)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER aarch64-none-elf-gcc)
set(CMAKE_LINKER aarch64-none-elf-ld)
set(CMAKE_OBJCOPY aarch64-none-elf-objcopy)
set(FLAGS -Wall -O2 -ffreestanding -nostdinc -nostdlib)
enable_language(ASM)
```
This project is licensed under the MIT License.

## Contributing
Pull requests are welcome! Open an issue for feature requests or bug reports.
