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


## Community

### IRC

To follow the project, discuss with us or contribute, please join us in
`#pyr0` on Rezosup (`irc.rezosup.org`).