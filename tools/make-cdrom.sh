#!/bin/bash

cp pyr0 root/kernel

grub-mkrescue -d /usr/lib/grub/i386-pc -o pyr0s.iso root
