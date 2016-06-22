# Python in ring 0 project (Pyr0)

[![Build Status](https://travis-ci.org/Saruta/pyr0.svg?branch=master)](https://travis-ci.org/Saruta/pyr0)
[![Join the chat at https://gitter.im/Saruta/pyr0](https://badges.gitter.im/Saruta/pyr0.svg)](https://gitter.im/Saruta/pyr0?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

## Description
Pyr0 is an attempt to make a python based Operating System,
it means that we use language feature to provide security
instead of using hardware as in a classical operating system.

The project is composed of two different parts: the core (which is a classical
kernel that manages memory, interrupts...) and the runtime (which manages
tasks, user programs...).

Another great idea of this project, is to have a plain-text userland.
Indeed, there is no binary in the root tree (except kernel :P), only
python scripts.

## Deps

- qemu (for emulation)
- libisoburn (for video)
- perl (for some scripts required by compilation)
- gcc/make (for compiling)

## Build/Install

- `./configure`
- `make`


## Usage

For interpreter mode:

- `make boot-i`

For file mode:

- `make boot`

or if you want a specific python's script:

- `make boot PYR0_ROM=path_to_python_script.py`

Example: `make boot PYR0_ROM=root/python/prime.py`

## Modules available:

### Pyr0 stdlib

- math: very light math module (TODO)
- os: os information
- sh: shell builtins

### Hardware information

- cpuinfo: cpu information
- smbios: various bios information
- pci: pci devices list

### Debug

- mem: memory debug module

### Misc

- morse: morse sound module (only on real hardware)

## Real hardware:

To try on real hardware (with usb key or cdrom), just dd the iso:
- `dd bs=4M if=pyr0s.iso of=/dev/your_device` 

## Notes
There are quite a lot of bugs, but of course, if you find a bug, please just
open an issue.

![alt tag](http://saruta.eu/res/pyr0.png)

## Community

### IRC

To follow the project, discuss with us or contribute, please join us in
`#pyr0` on Rezosup (`irc.rezosup.org`).
