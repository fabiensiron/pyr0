/*
 * File: memory.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: table management, page allocation, page_fault
 */
#include <atomos/types.h>
#include <atomos/string.h>
#include <atomos/mm.h>
#include <atomos/page.h>

void *_begin_load = &__begin_load;
void *_begin_kernel = &__begin_kernel;
void *_end_kernel = &__end_kernel;
void *_end_load = &__end_load;

/*
 * Paging
 */

int paging_init(u32 limit) // 32 mB
{
  u32 *pd0, *pt0;
  
  /* get kernel dir and tab */
  pd0 = (u32*)PD0_ADDR;
  pt0 = (u32*)PT0_ADDR;
  
  /* we know that there already is a kernel memory mapping
     in [0x000000-0x400000] 
  */

  /* clear first page to handle NULL pointers */
  memset((void *)0, 0, PAGE_SIZE);
  pt0[0] = 0;

  /* flush */
  flush_tlb_all();
}
