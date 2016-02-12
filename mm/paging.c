/*
 * File: paging.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: table management, page allocation, page_fault
 */
#include <atomos/types.h>
#include <atomos/string.h>
#include <atomos/mm.h>
#include <atomos/mman.h>
#include <atomos/console.h>

#include <asm/pgtable.h>

void *_begin_load = &__begin_load;
void *_begin_kernel = &__begin_kernel;
void *_end_kernel = &__end_kernel;
void *_end_load = &__end_load;

extern u32 k_top;

/*
 * Paging
 */

static inline
u32 *get_mirrored_pd(void)
{
  return (u32 *)(PAGING_MIRROR_VADDR + PAGE_SIZE * PDIR(PAGING_MIRROR_VADDR));
}

static inline
u32 *get_mirrored_pt(u32 pd_index)
{
  return (u32 *)(PAGING_MIRROR_VADDR + PAGE_SIZE*pd_index);
}

static inline
u8 is_in_mirrored_pd(u32 vaddr)
{
  return (vaddr >= PAGING_MIRROR_VADDR) &&
    (vaddr < PAGING_MIRROR_VADDR + PAGING_MIRROR_SIZE);
}

static
int paging_early_map(u32 *pd, u32 paddr, u32 vaddr)
{
  u32 *pt;
  u32 pdir_index = PDIR(vaddr);
  u32 ptab_index = PTABLE(vaddr);

  if (P_ISPRESENT(pd[pdir_index]))
    {
      pt =(u32 *) (pd[pdir_index] & PAGE_MASK);

      if (!P_ISPRESENT(pt[ptab_index]))
	;//	frame_ref((u32)pt);
      else
	return -1;
    }
  else
    {
      switch(pdir_index)
	{
	case 0:
	  memset ((u32*)PT0_ADDR, 0, PAGE_SIZE);
	  pd[0] = PT0_ADDR | P_KERNEL;
	  break;
	default:
	  {
	    pd[pdir_index] = (u32)frame_get();
	    
	    memset((u32 *)pd[pdir_index],0,PAGE_SIZE);
	    
	    if (pd[pdir_index] == 0)
	      return -1;
	    pd[pdir_index] |= P_KERNEL;
	  }
	}
      pt = (u32 *)(pd[pdir_index] & PAGE_MASK);
    }
  
  pt[ptab_index] = (paddr & PAGE_MASK) | P_KERNEL;
  
  return 0; // success
}

int paging_init(void) // 32 mB
{
  u32 *pd0;
  u32 paddr;
  
  /* get kernel dir and tab */
  pd0 = (u32*)PD0_ADDR;
  
  /* we know that there already is a kernel memory mapping
     in [0x000000-0x400000] 
  */
  memset(pd0, 0, PAGE_SIZE);
  
  for (paddr = PAGE_SIZE; paddr < k_top; paddr += PAGE_SIZE)
    if (paging_early_map(pd0, paddr, paddr))
      return -1;
  
  // mirroring
  pd0[PDIR(PAGING_MIRROR_VADDR)] = ((u32)pd0 & PAGE_MASK) | P_KERNEL;

  // install new directory
  SET_PAGE_DIR(PD0_ADDR);
  
  /* flush */
  flush_tlb_all();

  return 0;
}

int paging_map(u32 paddr, u32 vaddr, u16 flags)
{
  u32 pdir_index = PDIR(vaddr);
  u32 ptab_index = PTABLE(vaddr);

  u32 *pd = get_mirrored_pd();
  u32 *pt = get_mirrored_pt(pdir_index);

  /* test pd */
  if (is_in_mirrored_pd(vaddr))
    return -1;

  if (!P_ISPRESENT(pd[pdir_index]))
    {
      u32 *new_pt;
      if ((new_pt = frame_get()) == NULL)
	return -1;

      pd[pdir_index] = P_PRESENT | P_WRITABLE | ((u32)new_pt & PAGE_MASK);
      if (P_ISUSER(flags))
	pd[pdir_index] |= P_USER;

      invlpg((u32)pt);

      memset(pt, 0, PAGE_SIZE);
    }
  else if (!P_ISPRESENT(pt[ptab_index]))
    frame_ref(pd[pdir_index] & PAGE_MASK);
  else
    frame_unref(pt[ptab_index] & PAGE_MASK);

  pt[ptab_index] = P_PRESENT | (paddr & PAGE_MASK);
  pt[ptab_index] |= flags;

  invlpg(vaddr);
  
  return 0;
}

int paging_unmap(u32 vaddr)
{
  u32 pdir_index = PDIR(vaddr);
  u32 ptab_index = PTABLE(vaddr);

  u32 *pd = get_mirrored_pd();
  u32 *pt = get_mirrored_pt(pdir_index);

  int ret;

  if (!P_ISPRESENT(pd[pdir_index]) || !(P_ISPRESENT(pt[ptab_index])))
    return -1;

  if (is_in_mirrored_pd(vaddr))
    return -1;

  frame_unref(pt[ptab_index] & PAGE_MASK);

  pt[ptab_index] = 0;

  invlpg(vaddr);

  ret = frame_unref(pd[pdir_index] & PAGE_MASK);

  if (ret < 0)
    return -1;

  if (ret > 0)
    {
      pd[pdir_index] = 0;
      invlpg(pt);
    }
  
  return 0;
}

int paging_get_prot(u32 vaddr)
{
  u32 pdir_index = PDIR(vaddr);
  u32 ptab_index = PTABLE(vaddr);

  u32 *pd = get_mirrored_pd();
  u32 *pt = get_mirrored_pt(pdir_index);

  if (!P_ISPRESENT(pd[pdir_index]) || !(P_ISPRESENT(pt[ptab_index])))
    return PROT_NONE;

  return ((pd[pdir_index] & P_WRITABLE) && (pt[ptab_index] & P_WRITABLE))
    ? PROT_WRITE | PROT_READ
    : PROT_READ;
}

u32 paging_get_paddr(u32 vaddr)
{
  u32 pdir_index = PDIR(vaddr);
  u32 ptab_index = PTABLE(vaddr);
  u32 offset = POFFSET(vaddr);

  u32 *pd = get_mirrored_pd();
  u32 *pt = get_mirrored_pt(pdir_index);

  if (!P_ISPRESENT(pd[pdir_index]) || !(P_ISPRESENT(pt[ptab_index])))
    return 0;

  return (pt[ptab_index] & PAGE_MASK) + offset;
}

void do_page_fault()
{
  early_kdebug("Page fault !\n", 80);

  for (;;)
    ;
}
