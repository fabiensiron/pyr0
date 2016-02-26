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

#include <string.h>

#include "multiboot.h"

extern extmodule_t boot_module;

extern void trap_init ();
extern void init_IRQ ();

void setup_kernel (unsigned long magic, multiboot_info_t *info)
{ 
  serial_early_init();

  assert(magic == MULTIBOOT_BOOTLOADER_MAGIC);

  early_printk ("\n\nThis is ATOMOS booting pyr0\n");
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

  /* okay, this is a *ugly* hack, but it works if there is only 1 module */
  
  boot_module.addr = 0x4000;
  boot_module.len =
    ((module_t *)info->mods_addr)->mod_end -
    ((module_t *)info->mods_addr)->mod_start;
  /* set name to buf */
  boot_module.name = (char *)&boot_module.buf;

  memcpy(&boot_module.buf,(void *)(((module_t *)info->mods_addr)->string + sizeof(long)),64);

  memcpy((void*)0x4000,(void *)((module_t *)info->mods_addr)->mod_start, PAGE_SIZE);

  u32 nr_frames = frame_allocator_init(info->mem_upper * 1024);

  early_printk("Memory init %i frames\n", nr_frames);

  //  load_stack_info(); // FIXME

  /* NOTE: stack reset, do nothing here */

  return start_kernel (info);
}
