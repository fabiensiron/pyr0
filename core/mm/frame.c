/*
 * File: frame.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: frame (physical pages) management
 */
#include <atomos/kernel.h>
#include <atomos/types.h>
#include <atomos/mm.h>
#include <atomos/page.h>

#include <bsd/queue.h>

#include <string.h>

/*
 * frame allocator: a simple array with linked lists elements
 * TODO: check counters
 * TODO: try to invert frame in list (first at the beginning -> invert or double linked list)
 * TODO: debug function
 */

#define FRAME_DESCR_ARRAY_ADDR PAGE_ALIGN_UP((u32)_end_kernel)

struct frame_descr
{
  u32 paddr;
  u32 ref_count;
  LIST_ENTRY(frame_descr) links;
};

LIST_HEAD(frame_descr_head, frame_descr);

static struct frame_descr_head free_frames =
  LIST_HEAD_INITIALIZER(free_frames);

static struct frame_descr_head nonfree_frames =
  LIST_HEAD_INITIALIZER(nonfree_frames);

static struct frame_descr *frame_descr_array;

u32 mem_base, mem_top, k_top;
static u32 nr_frames, nr_nonfree_frames, nr_free_frames;

int frame_allocator_init(u32 mem_limit)
{
  struct frame_descr *descr_it;
  u32 addr_it;
  
  /* the size of the mem must be aligned */
  u32 mem_upper = PAGE_ALIGN_DOWN(mem_limit);
  
  /* init the lists */
  LIST_INIT(&free_frames);
  LIST_INIT(&nonfree_frames);

  /* and the counters */
  nr_frames = 0;
  nr_nonfree_frames = 0;
  nr_free_frames = 0;

  /* calculate the end of the kernel AND the frame array */
  k_top =
    FRAME_DESCR_ARRAY_ADDR +
    PAGE_ALIGN_UP((mem_upper >> PAGE_SHIFT)*sizeof(struct frame_descr));

  //  printk(KERN_INFO, "%x\n", FRAME_DESCR_ARRAY_ADDR);

  if (k_top >= mem_upper)
    return -1;

  /* set boundaries */
  mem_base = PAGE_SIZE;
  mem_top = mem_upper;

  /* init array */
  frame_descr_array = (struct frame_descr*)FRAME_DESCR_ARRAY_ADDR;

  for (addr_it = 0, descr_it = frame_descr_array;
       addr_it < mem_top;
       addr_it += PAGE_SIZE, descr_it++)
    {
      memset (descr_it, 0, sizeof(struct frame_descr));
      descr_it->paddr = addr_it;
	
      /* null frame */
      if (addr_it < mem_base)
	{
	  continue;
	}
      /* kernel big page */
      else if (addr_it < k_top)
	{
	  descr_it->ref_count = 1;
	  LIST_INSERT_HEAD(&nonfree_frames, descr_it, links);
	  nr_nonfree_frames++;
	}
      /* free */
      else
	{
	  descr_it->ref_count = 0;
	  LIST_INSERT_HEAD(&free_frames, descr_it, links);
	  nr_free_frames++;
	}
    }
  return nr_free_frames;
}

int frame_ref (u32 paddr)
{
  struct frame_descr *frame_descr;
  
  if (paddr & ~PAGE_MASK || (paddr < mem_base) || paddr > mem_top)
    return -1;

  frame_descr = frame_descr_array + (paddr >> PAGE_SHIFT);

  frame_descr->ref_count++;

  if (frame_descr->ref_count == 1)
    {
      LIST_REMOVE(frame_descr, links);
      LIST_INSERT_HEAD(&nonfree_frames, frame_descr, links);
      
      nr_free_frames--;
      nr_nonfree_frames++;

      return 1;
    }
  return 0;
}

int frame_ref_once (u32 paddr)
{
  struct frame_descr *frame_descr;

  if (paddr & ~PAGE_MASK || (paddr < mem_base) || paddr > mem_top)
    return -1;

  frame_descr = frame_descr_array + (paddr >> PAGE_SHIFT);

  if (frame_descr != 0)
    return 0;

  frame_descr->ref_count++;

  LIST_REMOVE(frame_descr, links);
  LIST_INSERT_HEAD(&nonfree_frames, frame_descr, links);

  nr_free_frames--;
  nr_nonfree_frames++;

  return 1;
}

int frame_unref(u32 paddr)
{
  struct frame_descr *frame_descr;
  
  if (paddr & ~PAGE_MASK || (paddr < mem_base) || paddr > mem_top)
    return -1;

  frame_descr = frame_descr_array + (paddr >> PAGE_SHIFT);

  if (frame_descr->ref_count <= 0)
    return -1;

  frame_descr->ref_count--;

  if (frame_descr->ref_count == 0)
    {
      LIST_REMOVE(frame_descr, links);
      LIST_INSERT_HEAD(&free_frames, frame_descr, links);
      
      nr_nonfree_frames--;
      nr_free_frames++;

      return 1;
    }

  return 0;
}

void *frame_get ()
{
  struct frame_descr *frame_descr;
  if (LIST_EMPTY(&free_frames))
    return NULL;

  frame_descr = LIST_FIRST(&free_frames);
  LIST_REMOVE(frame_descr, links);

  nr_free_frames--;

  if (frame_descr->ref_count != 0)
    return NULL;

  frame_descr->ref_count++;

  LIST_INSERT_HEAD(&nonfree_frames, frame_descr, links);
  nr_nonfree_frames++;

  return (void *)frame_descr->paddr;
}
