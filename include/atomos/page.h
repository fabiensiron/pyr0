/*
 * File: page.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: macros for processor's pagination
 */

#ifndef _PAGE_H_
# define _PAGE_H_

# define PAGE_SHIFT    12
# define PAGE_SIZE     (1UL << PAGE_SHIFT)
# define PAGE_MASK     (~(PAGE_SIZE-1))


# define PAGE_ALIGN_UP(addr)         (((addr)+PAGE_SIZE-1)& PAGE_MASK)
# define PAGE_ALIGN_DOWN(addr)       ((addr) & PAGE_MASK)

# define PDIR(P)       (((u32)P) >> 22)
# define PTABLE(P)     ((((u32)P) >> 12) & 0x3ff)
# define POFFSET(P)    (((u32)P) & 0xfff)


#endif /* !_PAGE_H_ */
