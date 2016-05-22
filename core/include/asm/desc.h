/*
 * File: desc.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: stuff about descriptors
 */

#ifndef _ASM_DESC_H_
# define _ASM_DESC_H_

/* types about descriptors (aka: asm/desc_defs.h in linux) */
# include <kernel/types.h>

struct desc_struct
{
  u16 limit0;
  u16 base0;
  u8 base16;
  u8 t: 4;
  u8 dtype: 1;
  u8 dpl: 2;
  u8 p: 1;
  u8 limit16: 4;
  u8 avl: 1;
  u8 l: 1;
  u8 dsize: 1;
  u8 g: 1;
  u8 base24;
} __attribute__((packed));

enum gate_type
  {
    INTERRUPT = 0x6,
    TRAP  =  0x7
  };

struct gate_desc
{
  u16 offset0;
  u16 sel;
  u8 reserved: 5;
  u8 z: 3;
  u8 type: 3;
  u8 d: 1;
  u8 z2: 1;
  u8 dpl: 2;
  u8 p: 1;
  u16 offset31;
} __attribute__((packed));

struct desc_ptr
{
  u16 size;
  u32 ptr;
} __attribute__((packed));

extern struct gate_desc idt_table[];

struct gdt_struct
{
  struct desc_struct gdt[GDT_ENTRIES];
} __attribute__((aligned(0x1000)));

# define GDT_ENTRY_INIT(flags, base, limit) {	\
	  .limit0 = limit & 0xffff,		\
	  .base0  = base & 0xffff,		\
	  .base16 = (base >> 16) & 0xff,	\
	  .t = flags & 0xf,			\
	  .dtype = (flags >> 4) & 0x1,		\
	  .dpl = (flags >> 5) & 0x3,		\
	  .p = (flags >> 7) & 0x1,		\
	  .limit16 = (limit >> 16) & 0xf,	\
	  .avl = (flags >> 12) & 0x1,		\
	  .l = (flags >> 13) & 0x1,				\
	  .dsize = (flags >> 14) & 0x1,				\
	  .g = (flags >> 15) & 0x1,				\
	  .base24 = (base >> 24) & 0xff,			\
}


/* 
 * Inline functions and macros to avoid inline assembly in c
 *   files.
 */

# define load_gdt(dtr)  __load_gdt(dtr)
# define load_idt(dtr)  __load_idt(dtr)
# define load_tr(tr)    __load_tr(tr)

static inline
void __load_gdt(const struct desc_ptr *dtr)
{
  __asm__ volatile("lgdt %0"::"m" (*dtr));
}

static inline
void __load_idt(const struct desc_ptr *dtr)
{
  __asm__ volatile("lidt %0"::"m" (*dtr));
}

static inline
void __load_tr(const struct desc_ptr *dtr)
{
  __asm__ volatile("ltr %0"::"m" (*dtr));
}

#endif /*!_ASM_DESC_H_ */
