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

# define PDBOOT_ADDR     0x0000
# define PTBOOT_ADDR     0x1000
# define PD0_ADDR        0x2000
# define PT0_ADDR        0x3000

extern u32 __begin_load;
extern u32 __begin_kernel;
extern u32 __end_kernel;
extern u32 __end_load;

extern void *_begin_load;
extern void *_begin_kernel;
extern void *_end_kernel;
extern void *_end_load;

/**
 * FRAME ALLOCATOR
 */
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

/**
 * PAGING MANAGER
 */

# define PAGING_MIRROR_VADDR 0x3fc00000 /* 1gB - 4mB */
# define PAGING_MIRROR_SIZE  (1 << 22)  /* 4mB */

/**
 * paging_init - init the paging manager
 *
 * @return: -1 if error, 0 otherwise
 */
int paging_init(void);
/**
 * paging_map - map a vaddr to a paddr
 * @param paddr: physical addr / frame
 * @param vaddr: virtual address / page
 * @param user: user prot, meaning no kernel access
 * @param flags: TODO
 * 
 * @return: 1 okay, 0 otherwise
 */
int paging_map(u32 paddr, u32 vaddr, u16 flags);
/**
 * paging_unmap - unmap a vaddr to the correspondant paddr
 * @param vaddr: virtual address /page
 *
 * @return: 1 okay, 0 otherwise
 */
int paging_unmap(u32 vaddr);
/**
 * paging_get_prot - return the protection of the correspondant page
 * @param vaddr: virtual address / page
 *
 * @return:  PROT_NONE if error, flags PROT_READ PROT_WRITE otherwise
 */
int paging_get_prot(u32 vaddr);
/**
 * paging_get_paddr - return the correspondant frame address
 * @param: virtual address - page
 *
 * @return: 0 if error, physical address otherwise
 */
u32 paging_get_paddr(u32 vaddr);

# define invlpg(addr) __asm__ volatile ("invlpg %0": : "m"(addr): "memory")
# define flush_tlb_all() __asm__ volatile ("movl %%cr3, %%eax\n\tmovl %%eax, %%cr3":::"ax")


#endif /*!_MM_H_*/
