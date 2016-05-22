/*
 * File: vmm.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: first fit memory allocator to manage vmm
 */
#ifndef _VMM_H_
# define _VMM_H_

# include <kernel/slab.h>
# include <kernel/pyr0.h>

struct vmm_range;

int vmm_setup(u32 kern_base, u32 kern_top, u32 stack_bottom, u32 stack_top);
struct vmm_range *vmm_new_range(u32 nb_pages, u32 flags, u32 *range_start);
int vmm_del_range(struct vmm_range *range);
u32 vmm_alloc(u32 nb_pages, u32 flags);
int vmm_free(u32 vaddr);
int vmm_set_slab(struct vmm_range *range, struct slab *slab);
struct slab*vmm_resolve_slab(u32 vaddr);
int vmm_is_valid_vaddr(u32 vaddr);

#endif /*!_VMM_H_*/
