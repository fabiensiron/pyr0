/*
 * File: kmalloc.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: physical contiguous memory allocation (kmalloc)
 */

#include <kernel/pyr0.h>
#include <kernel/mm.h>
#include <kernel/mman.h>
#include <kernel/kmalloc.h>

#include <asm/pgtable.h>

/*
 * tmp malloc of kernel/pyr0
 * dummy first fit on 4 MB
 */

void *brk_base = (void *)0x400000;
static void *brk;
void *brk_limit = (void *)0x1000000;

void *sbrk(ssize_t inc)
{
	void *res = brk;
	if (res + inc >= brk_limit)
		panic("Heap full !\n");

	brk += inc;

	return res;
}

/* helper macros */
#define CHUNK_OF_(PTR_)						\
	((struct chunk*)((char *)PTR_ - sizeof(struct chunk)))

#define ASSERT_CHUNK(b)						\
	assert(b->data == ((char *)b + sizeof(struct chunk)))

/* helper inline functions */
static inline
size_t word_align(size_t n)
{
	return (n + sizeof(size_t)-1) & ~(sizeof(size_t) -1);
}

static inline
void wordcpy(void *dst, void *src, size_t len)
{
	for(;len != 0;len -= sizeof(size_t), src += sizeof(size_t),
		    dst+= sizeof(size_t))
		*(size_t*)dst = *(size_t*)src;
}

static inline
void zerofill(void *ptr, size_t len)
{
	for (; len != 0; len -= sizeof(size_t), ptr += sizeof(size_t))
		*(size_t*)ptr = 0;
}

struct chunk
{
	struct chunk *next, *prev;
	size_t               size;
	long                 free;
	void                *data;
};

static
struct chunk *get_base(void)
{
	static struct chunk *base = NULL;

	if (base == NULL)
	{
		void *old, *p;
		p = sbrk (0);
		old = sbrk(sizeof(struct chunk));
		assert (p == old);
		base = old;
		base->next = NULL;
		base->prev = NULL;
		base->size = 0;
		base->free = 0;
	}
	return base;
}

static
int extend_heap (struct chunk *last, size_t size)
{
	void *old, *p;
	struct chunk *new_chunk;
	size_t aligned_size;

	aligned_size = word_align(size + sizeof(struct chunk));

	p = sbrk(0);
	old = sbrk(aligned_size);

	assert(p == old);

	new_chunk = old;
	new_chunk->prev = last;
	new_chunk->next = NULL;
	new_chunk->size = size;
	new_chunk->free = 0;
	new_chunk->data = (char *)new_chunk + sizeof(struct chunk);

	last->next = new_chunk;

	return 1;
}

static
struct chunk *get_chunk (void *p)
{
	void *brk_ = sbrk(0);
	void *base = get_base();

	if (p == NULL ||
	    (word_align((size_t)p) != (size_t)p) ||
	    p > brk_ ||
	    p < base)
		return NULL;

	struct chunk *curr_chunk = CHUNK_OF_(p);

	if (p != curr_chunk->data)
		return NULL;

	return curr_chunk;
}

static
struct chunk *find_chunk(size_t size)
{
	struct chunk *curr_chunk;
	curr_chunk = get_base();

	for (;
	     curr_chunk->next &&
		     ((curr_chunk->next->free == 0) ||
		      (curr_chunk->next->size < size));
	     curr_chunk = curr_chunk->next
		)
		;

	return curr_chunk;
}

void *kmalloc(size_t size)
{
	size_t aligned_size;
	struct chunk *curr_chunk;

	if (size == 0) return NULL;

	aligned_size = word_align (size);
	curr_chunk = find_chunk(aligned_size);

	if (curr_chunk->next == NULL)
		if (extend_heap(curr_chunk, aligned_size) == 0)
			return NULL;

	curr_chunk = curr_chunk->next;
	curr_chunk->free = 0;

	ASSERT_CHUNK(curr_chunk);

	return curr_chunk->data;
}

void *kcalloc(size_t nb, size_t size)
{
	void *r;
	r = kmalloc(nb * size);

	size_t aligned_size = word_align(nb * size);

	if (r != NULL)
		zerofill(r, aligned_size);

	return r;
}

# define MIN(a, b) ((a>b)?b:a)

void *krealloc(void *old, size_t newsize)
{
	struct chunk *old_chunk;
	void *new = NULL;
	size_t oldsize;

	if (old == NULL)
		return kmalloc (newsize);
	if (newsize != 0)
	{
		old_chunk = get_chunk(old);
		oldsize = old_chunk->size;

		if (newsize < oldsize) return old;

		new = kmalloc(newsize);

		if (new == NULL) return NULL;

		size_t len = word_align(MIN(oldsize, newsize));
		wordcpy (new, old, len);
	}

	kfree (old);

	return new;
}

void kfree (void *p)
{
	struct chunk *curr_chunk = get_chunk(p);
	if (curr_chunk == NULL) return;
	if (p != curr_chunk->data) return;

	curr_chunk->free = 1;
}

void kmalloc_init (void)
{
	unsigned int i;
	void *paddr;
	brk = brk_base;
	u32 vaddr = (u32)brk;

	for (i = 0; i < ((brk_limit - brk) / PAGE_SIZE); i++, vaddr += PAGE_SIZE)
	{
		paddr = frame_get();
		assert(paddr != NULL);
		assert(paging_map((u32)paddr, vaddr, P_KERNEL) == 0);
	}
}
