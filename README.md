# Python in ring 0 project (Pyr0)

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

## Build/Install

- `./configure`
- `make`


## Usage
- `make boot`

or if you want a specific python's script:

- `make boot PYR0_ROM=path_to_python_script.py`

Example: `make boot PYR0_ROM=root/python/prime.py`

## Notes
There are quite a lot of bugs, but of course, if you find a bug, please just
open an issue.

## Community

### IRC

To follow the project, discuss with us or contribute, please join us in
`#pyr0` on Rezosup (`irc.rezosup.org`).
