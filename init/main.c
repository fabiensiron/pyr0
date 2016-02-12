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

#include <asm/system.h>

#include "../boot/multiboot.h"

void start_kernel(multiboot_info_t *info)
{
  unsigned long long int i;
  
  early_kdebug("start kernel ...\n", 20);
  
  if (!(info->flags & (1 << 6)))
    hlt();

  memory_map_t *mmap = (void *)info->mmap_addr;

  
  while ((u32)mmap < info->mmap_addr + info->mmap_length)
    {
      if (mmap->type == 2)
	{
	  for (i = 0; i < mmap->length_low; i += 0x1000)
	    {
	      if (mmap->base_addr_high > 0) continue;
	      frame_ref_once ((mmap->base_addr_low + i) & PAGE_MASK);
	    }
	}
      mmap = (memory_map_t *)((u32)mmap + mmap->size + sizeof(u32));
    }

  /* mem/paging */
  if (paging_init())
    early_kdebug("Fatal error: memory cannot be mapped\n", 80);

  for (;;)
    ;
}

void init(void)
{
}
