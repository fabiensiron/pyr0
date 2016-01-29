/*
 * File: early_pagination.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: Identity mapping of the first 4MB
 *   and copy of this first *big* page into [0xc0000000-0xc0400000]
 */

#include <atomos/types.h>

# define PD0_ADDR 0x1000
# define PT0_ADDR 0x2000

void init_early_pagination (void)
{
  unsigned i;
  u32 *pd0;
  u32 *pt0;
  u32 page_it;

  pd0 = (u32*)PD0_ADDR;
  
  for (i = 0; i < 1024; i++)
    pd0[i] = 0;
  
  pd0[0] = PT0_ADDR;
  pd0[0] |= 3;
  pd0[768] = pd0[0];

  pt0 = (u32*)PT0_ADDR;

  page_it = 0;
  for (i = 0; i < 1024; i++)
    {
      pt0[i] = page_it;
      pt0[i] |= 3;
      page_it += 4096;
    }

  __asm__ volatile
    ("movl %0, %%eax \n \t \
      movl %%eax, %%cr3 \n \t \
      movl %%cr0, %%eax \n \t \
      orl $0x80000000, %%eax \n \t \
      movl %%eax, %%cr0 \n \t"::"i"(PD0_ADDR):"eax");

}
