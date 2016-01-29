/*
 * File: pm.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: macros for segmentation
 */

#ifndef _ASM_SEGMENT_H_
# define _ASM_SEGMENT_H_

# define SELECTOR(Entry, Rpl)    ((Entry << 3) | Rpl)

# define USER_RPL                 0x3
# define KERNEL_RPL               0x0

/* GDT_ENTRIES */
# define GDT_ENTRY_NULL           0

# define GDT_ENTRY_KERNEL_CS      1
# define __KERNEL_CS              SELECTOR(GDT_ENTRY_KERNEL_CS, KERNEL_RPL)

# define GDT_ENTRY_KERNEL_DS      2
# define __KERNEL_DS              SELECTOR(GDT_ENTRY_KERNEL_DS, KERNEL_RPL)

# define GDT_ENTRY_USER_CS        3
# define __USER_CS                SELECTOR(GDT_ENTRY_USER_CS, USER_RPL)

# define GDT_ENTRY_USER_DS        4
# define __USER_DS                SELECTOR(GDT_ENTRY_USER_DS, USER_RPL)

/* segment for fs ? */

# define GDT_ENTRY_TSS            5
/* TODO: __KERNEL_TSS */

# define GDT_ENTRIES              6

# define SEGMENT_RPL_MASK         0x3
# define SEGMENT_TI_MASK          0x4

# define SEGMENT_GDT              0x0
# define SEGMENT_LDT              0x4

# define GDT_SIZE                 (GDT_ENTRIES * 8)

//# define CODE_SEG(Dpl)            (((Dpl) << 5) | (1 << 4) | 0xA)
//# define DATA_SEG(Dpl)        (((Dpl) << 5) | (1 << 4) | 0x3)
/* TODO: TSS_SEG(Dpl) */

# define IDT_ENTRIES              255
# define IDT_SIZE                 (IDT_ENTRIES * 8)

#endif /* !_ASM_SEGMENT_H_ */
