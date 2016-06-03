# Python in ring 0 project (Pyr0)

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

## Notes
There are quite a lot of bugs, but of course, if you find a bug, please just
open an issue.

![alt tag](http://saruta.eu/res/pyr0.png)

## Community

### IRC

To follow the project, discuss with us or contribute, please join us in
`#pyr0` on Rezosup (`irc.rezosup.org`).
