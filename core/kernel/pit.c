/*
 * File: pit.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: driver for i8253 timer
 */

#include <asm/io.h>

#include <atomos/kernel.h>
#include <atomos/interrupt.h>

# define INTERNAL_FREQUENCY 1193182
# define FREQUENCY 100 // Hz

static unsigned long tick = 0;

void pit_wrapper (void);

void pit_routine (void)
{
  ++tick;
}

void pit_init (void)
{
  //  t_uint16 count = 11931;
  u16 count = INTERNAL_FREQUENCY / FREQUENCY;
  outb(0x43,0x34);
  outb(0x40,count & 0x00ff);
  outb(0x40,(count & 0xff00) >> 8);

  //  printk(KERN_INFO, "PIT init !\n");

  setup_irq(0, pit_routine);
}

unsigned long gettick ()
{
  return tick*10;
}

void sleep (u32 duration)
{
  unsigned t = gettick ();

  while (gettick () - t <= duration)
    ;
}

