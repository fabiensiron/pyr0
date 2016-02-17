/*
 * File: setup.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: mostly arch-dependent setup
 */

#include <atomos/kernel.h>
#include <atomos/console.h>
#include <atomos/serial.h>

#include <asm/processor.h>
#include <asm/system.h>
#include <asm/pgtable.h>

#include <atomos/mm.h>
#include <atomos/page.h>

#include "multiboot.h"

extern int sprintf(char *buf, const char *fmt, ...);
extern void trap_init ();
extern void init_IRQ ();

static 
void die (const char *msg)
{
  early_printk ("######### PANIC #########\n");
  early_printk ("  Error: %s\n", msg);
  early_printk ("  Halt processor...\n");

  hlt();
}

void setup_kernel (unsigned long magic, multiboot_info_t *info)
{ 
  serial_early_init();
  //  early_console_init ();

  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    die ("Wrong bootloader");

  early_printk ("Welcome in ATOMOS !\n");
  early_printk ("boot sequence ...\n");

  init_early_pagination ();
  
  cpu_init ();
  
  trap_init ();

  init_IRQ ();

  sti();

  if (!(info->flags & (1 << 6)))
      die ("Memory map unavailable !\n");

  u32 nr_frames = frame_allocator_init(info->mem_upper * 1024);

  early_printk("Memory init %x frames\n", nr_frames);

  //  load_stack_info(); // FIXME

  /* NOTE: stack reset, do nothing here */

  return start_kernel (info);
}
