/*
 * File: malloc.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: wrapper for core malloc (kmalloc and friends)
 */
#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <atomos/types.h>
#include <atomos/kmalloc.h>

static inline void *malloc(size_t s)
{
  return kmalloc(s);
}
static inline void *calloc(size_t s, size_t n)
{
  return kcalloc(s, n);
}
static inline void *realloc(void *p, size_t s)
{
  return krealloc(p, s);
}
static inline void free(void *p)
{
  kfree(p);
}

#endif /* _MALLOC_H_ */

