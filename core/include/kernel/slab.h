/*
 * File: slab.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: slab allocator
 */

#ifndef _SLAB_H_
# define _SLAB_H_

# include <kernel/vmm.h>
# include <kernel/kernel.h>

struct slab_cache;
struct slab;
struct slab_free_object;

struct slab_cache *
slab_cache_setup_prepare(u32 kernel_base,
			 u32 kernel_top,
			 size_t sizeof_struct_range,
			 struct slab **first_struct_slab_of_caches,
			 u32 *first_slab_of_caches_base,
			 u32 *first_slab_of_caches_nb_pages,
			 struct slab **first_struct_slab_of_ranges,
			 u32 *first_slab_of_ranges_base,
			 u32 *first_slab_of_ranges_nb_pages);
int slab_cache_setup_commit(struct slab *first_struct_slab_of_caches,
			struct vmm_range *first_range_of_caches,
			struct slab *first_struct_slab_of_ranges,
  			struct vmm_range *first_range_of_ranges);
struct slab_caches *slab_cache_create(const char *name,
				      size_t obj_size,
				      u32 pages_per_slab,
				      u32 min_free_objs,
				      u32 cache_flags);
int slab_cache_destroy(struct slab_cache *slab_cache);
u32 slab_cache_alloc(struct slab_cache *slab_cache, u32 alloc_flags);
u32 slab_cache_free(u32 vaddr);
struct vmm_range **
slab_cache_release_struct_range(struct vmm_range *the_range);

#endif /*!_SLAB_H_*/
