/*
 * File: kmalloc.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: kmalloc and friends
 */

#ifndef _KMALLOC_H_
# define _KMALLOC_H_

void *kmalloc(size_t size);
void *kcalloc(size_t nb, size_t size);
void *krealloc(void *old, size_t newsize);
void kfree(void *p);
void kmalloc_init(void);

#endif /* _KMALLOC_H_*/
