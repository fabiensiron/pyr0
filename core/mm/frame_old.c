/*
 * File: frame.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: physical memory manager
 */

# include <kernel/kernel.h>
# include <kernel/page.h>

# include <asm/pgtable.h>

# include <string.h>

# define PAGE(addr) (addr >> PAGE_SHIFT)
# define MAX_RAM (128 * 1024 * 1024) // 128MB
# define NR_FRAMES (MAX_RAM / PAGE_SIZE)
# define BITMAP_LEN (NR_FRAMES / 8)

u8 mem_bitmap[BITMAP_LEN];

static inline void
set_frame(u32 frame)
{
  mem_bitmap[frame/8] |= 1 << (frame % 8);
}

void release_frame(u32 paddr)
{
  mem_bitmap[paddr / PAGE_SIZE /8] &= ~(1 << ((paddr/PAGE_SIZE)% 8));
}

u32 get_frame()
{
  unsigned i, j, page;
  
  for(i = 0; i < BITMAP_LEN; i++)
    if (mem_bitmap[i] != 0xff)
      {
	for (j = 0; j < 8; j++)
	  if (!(mem_bitmap[i] & (1 << j)))
	    {
	      page = 8 * i + j;
	      set_frame(page);
	      return page * PAGE_SIZE;
	    }
      }

  return -1;
}

u32 mem_init()
{
  int it;
  
  memset(&mem_bitmap, 0, BITMAP_LEN);

  /* set the 4 first MB used (kernel) */
  for (it = 0; it < 0x400000; it+= PAGE_SIZE)
    set_frame(PAGE(it));

  /* return numb pages avail */
  return NR_FRAMES - PT_SIZE;
}
