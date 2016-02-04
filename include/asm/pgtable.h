/*
 * File: pgtable.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: macros for processor's pagination
 */

#ifndef _PGTABLE_H_
# define _PGTABLE_H_

# define SET_PAGE_DIR(pgdir)				\
  do {							\
    __asm__ volatile ("movl %0,%%cr3"::"r" (pgdir));	\
  } while (0)

# define P_NULL                   0
# define P_PRESENT                1
# define P_WRITABLE               (1 << 1)
# define P_USER                   (1 << 2)

# define PD_SIZE                  1024
# define PT_SIZE                  1024

#endif /* !_PGTABLE_H_ */
