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


# define PAGE_ALIGN_UP         (((addr)+PAGE_SIZE-1)& PAGE_MASK)
# define PAGE_ALIGN_DOWN       (((addr) & PAGE_MASK)

#endif /* !_PAGE_H_ */
