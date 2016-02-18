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

extern void trap_init ();
extern void init_IRQ ();

void setup_kernel (unsigned long magic, multiboot_info_t *info)
{ 
  serial_early_init();

  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    panic("Wrong bootloader\n");

  early_printk ("This is ATOMOS booting pyr0\n");
  early_printk ("boot sequence ...\n");

  init_early_pagination ();
  early_printk ("early paging init\n");
  
  cpu_init ();
  early_printk ("cpu init\n");
  
  trap_init ();
  early_printk ("traps init\n");

  init_IRQ ();
  early_printk ("irq init\n");

  sti();
  early_printk ("interrupts enabled !\n");

  if (!(info->flags & (1 << 6)))
      panic ("Memory map unavailable !\n");

  u32 nr_frames = frame_allocator_init(info->mem_upper * 1024);

  early_printk("Memory init %i frames\n", nr_frames);

  //  load_stack_info(); // FIXME

  /* NOTE: stack reset, do nothing here */

  return start_kernel (info);
}
