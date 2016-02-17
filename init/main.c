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

extern int sprintf(char *buf, const char *fmt, ...);
extern u32 k_top;

void test_paging()
{
  u32 new_frame;
  u32 vaddr = PAGE_ALIGN_DOWN((u32)test_paging);

  u32 tmp_vaddr = (k_top + PAGE_SIZE);
  
  new_frame = (u32)frame_get();

  if (!new_frame)
    early_printk("Fatal error");



  paging_map(new_frame, tmp_vaddr, P_WRITABLE);
  
  frame_unref(new_frame);


  memcpy((void *)tmp_vaddr, (void *)vaddr, PAGE_SIZE);

  paging_map(new_frame, vaddr, P_WRITABLE);

  paging_unmap(tmp_vaddr);

  early_printk("first test okay\n", 40);


  for(;;)
    ;
}

void start_kernel(multiboot_info_t *info)
{
  unsigned long long int i;
  
  tty_init();
  
  early_printk("start kernel ...\n");
  
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
    early_printk("Fatal error: memory cannot be mapped\n", 80);




  for (;;)
    ;
}

void init(void)
{
}
