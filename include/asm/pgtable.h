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
# define P_WRITE_THROUGH          (1 << 3)
# define P_NO_CACHING             (1 << 4)
# define P_ACCESSED               (1 << 5)
# define P_DIRTY                  (1 << 6)
# define P_4M                     (1 << 7)
# define P_PAT                    (1 << 7)
# define P_GLOBAL                 (1 << 8)

# define P_KERNEL                 (P_PRESENT | P_WRITABLE)
# define P_USER_RO                (P_PRESENT | P_USER)
# define P_USER_RW                (P_PRESENT | P_WRITABLE | P_USER)

# define P_ISFLAG(Flag, Mask)			\
  ((Flag) & Mask)

# define P_ISPRESENT(P)           P_ISFLAG((P), P_PRESENT)
# define P_ISWRITABLE(P)          P_ISFLAG((P), P_WRITABLE)
# define P_ISUSER(P)              P_ISFLAG((P), P_USER)

# define PD_SIZE                  1024
# define PT_SIZE                  1024

#endif /* !_PGTABLE_H_ */
