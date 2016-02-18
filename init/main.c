/*
 * File main.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: setup the operating system (mostly non arch-dependent) and 
 *   spawn the first process (init)
 */
#include <atomos/kernel.h>
#include <atomos/console.h>
#include <atomos/mm.h>
#include <atomos/mman.h>
#include <atomos/string.h>
#include <atomos/serial.h>
#include <atomos/tty.h>

#include <asm/system.h>
#include <asm/pgtable.h>

#include "../boot/multiboot.h"

void start_kernel(multiboot_info_t *info)
{
  unsigned long long int i;
  
  tty_init();
  
  printk(KERN_INFO, "tty init\n");
  
  printk(KERN_INFO, "start kernel ...\n");
  
  if (!(info->flags & (1 << 6)))
    hlt();

  memory_map_t *mmap = (void *)info->mmap_addr;
  
  printk(KERN_INFO, "init mapping...\n");
  
  while ((u32)mmap < info->mmap_addr + info->mmap_length)
    {
      if (mmap->type == 2)
	{
	  for (i = 0; i < mmap->length_low; i += 0x1000)
	    {
	      if (mmap->base_addr_high > 0) continue;
	      frame_ref_once ((mmap->base_addr_low + i) & PAGE_MASK);
	    }
	  printk(KERN_INFO, "lock frame\n");
	}
      mmap = (memory_map_t *)((u32)mmap + mmap->size + sizeof(u32));
    }

  printk(KERN_INFO, "paging init...\n");
  /* mem/paging */
  if (paging_init())
    panic("Fatal error: memory cannot be mapped\n");

  printk(KERN_INFO, "Atomos boot process done\n");


  for (;;)
    ;
}

void init(void)
{
}
