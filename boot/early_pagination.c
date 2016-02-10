/*
 * File: early_pagination.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: Identity mapping of the first 4MB
 *   [0x000000-0x400000]
 */

#include <atomos/types.h>
#include <atomos/mm.h>
#include <atomos/page.h>

#include <asm/pgtable.h>
#include <asm/system.h>

void init_early_pagination (void)
{
  unsigned i;
  u32 *pd0;
  u32 *pt0, *pt1;
  u32 page_it;

  pd0 = (u32*)PD0_ADDR;
  
  for (i = 0; i < PD_SIZE; i++)
    pd0[i] = P_NULL;
  
  pd0[1] = PT1_ADDR | P_PRESENT | P_WRITABLE;
  pd0[0] = PT0_ADDR | P_PRESENT | P_WRITABLE;

  pt0 = (u32*)PT0_ADDR;
  pt1 = (u32*)PT1_ADDR;

  page_it = 0;
  for (i = 0; i < PT_SIZE; i++)
    {
      pt0[i] = page_it | P_PRESENT | P_WRITABLE;
      page_it += PAGE_SIZE;
    }

  for (i = 0; i < PT_SIZE; i++)
    {
      pt1[i] = page_it | P_PRESENT | P_WRITABLE;
      page_it += PAGE_SIZE;
    }

  SET_PAGE_DIR(PD0_ADDR);

  set_cr0(get_cr0() | CR0_PG | CR0_WP);
}
