/*
 * File: mm.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: memory stuff
 */

#ifndef _MM_H_
# define _MM_H_

# include <atomos/types.h>
# include <atomos/page.h>

# define PD0_ADDR        0x1000
# define PT0_ADDR        0x2000
# define PT1_ADDR        0x3000

extern u32 __begin_load;
extern u32 __begin_kernel;
extern u32 __end_kernel;
extern u32 __end_load;

extern void *_begin_load;
extern void *_begin_kernel;
extern void *_end_kernel;
extern void *_end_load;

/* frame (phys pages) management */
//void release_frame(u32 paddr);
//u32 get_frame(void);
//u32 mem_init(void);

/**
 * frame_allocator_init - init the physical page manager
 * @param mem_limit: top of the memory
 * 
 * @return: -1 if error otherwise the number of free frames init.
 */
int frame_allocator_init(u32 mem_limit);
/**
 * frame_ref - reference a frame (increment reference counter or allocate)
 * @param paddr: physical address, must be aligned
 *
 * @return: -1 if error, 1 if allocate, 0 if just inc the ref count
 */
int frame_ref(u32 paddr);
/**
 * frame_ref_once - reference a frame once (allocate or do nothing)
 * @param paddr: physical address, must be aligned
 *
 * @return: -1 if error, 1 if allocate, 0 if nothing
 */
int frame_ref_once(u32 paddr);
/**
 * frame_unref - unreference a frame (decrement reference counter or deallocate)
 * @param paddr: physical address, must be aligned
 *
 * @return: -1 if error, 1 if deallocate, 0 if just dec the ref count
 */
int frame_unref(u32 paddr);
/**
 * frame_get - allocate a frame 
 *
 * @return: NULL if error, otherwise address of the frame
 */
void *frame_get(void);


# define flush_tlb(addr) __asm__ volatile ("invlpg %0": : "m"(addr): "memory")
# define flush_tlb_all() __asm__ volatile ("movl %%cr3, %%eax\n\tmovl %%eax, %%cr3":::"ax")


#endif /*!_MM_H_*/
