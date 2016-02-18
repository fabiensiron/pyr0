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
  u32 *pt0;
  u32 page_it;

  pd0 = (u32*)PDBOOT_ADDR;
  
  for (i = 0; i < PD_SIZE; i++)
    pd0[i] = P_NULL;
  
  pd0[0] = PTBOOT_ADDR | P_PRESENT | P_WRITABLE;

  pt0 = (u32*)PTBOOT_ADDR;

  page_it = 0;
  for (i = 0; i < PT_SIZE; i++)
    {
      pt0[i] = page_it | P_PRESENT | P_WRITABLE;
      page_it += PAGE_SIZE;
    }

  SET_PAGE_DIR(PDBOOT_ADDR);

  set_cr0(get_cr0() | CR0_PG | CR0_WP);
}
