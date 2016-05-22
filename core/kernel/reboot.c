/*
 * File: reboot.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 */
#include <kernel/pyr0.h>

#include <asm/io.h>
#include <asm/system.h>

void reboot(void)
{
  u8 good;
  
  cli();

  while(good & 0x02)
      good = inb(0x64);

  outb(0x64, 0xfe);
  
  hlt();
}
