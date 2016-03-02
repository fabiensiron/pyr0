/*
 * File: system.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: misc system
 */

#ifndef _SYSTEM_H_
# define _SYSTEM_H_

# include <atomos/types.h>
# include <asm/segment.h>

# define DEF_SEG(Name)						\
  static inline void loadsegment_ ## Name (u16 val)		\
  {								\
    __asm__ volatile						\
      ("movw %0, %%" #Name " \n \t"::"r" (val): "memory");	\
  }

DEF_SEG(ds)
DEF_SEG(es)
DEF_SEG(fs)
DEF_SEG(gs)
DEF_SEG(ss)

static inline void loadsegment_cs(u32 val)
{
  __asm__ volatile
    ("pushl %0 \n \t \
      pushl $1f \n \t \
      lret \n \t \
      1: \n\t"::"r" (val):"memory");
}

//# define loadsegment(seg, val) loadsegment_ ## seg(val)

# define MAIN_KERNEL_STACK 0x9fffc /* just below video mem */

static inline
void set_gate (void *gate_addr, u8 type, u8 dpl, void *addr)
{
  *(u32*)gate_addr = (u32)(((u32)addr & 0xffff) | (__KERNEL_CS << 16));
  *(1+(u32*)gate_addr) = (u32)(((u32)addr & 0xffff0000) |
			       (0x8000 | (dpl << 13) | (type << 8)));
}

# define set_trap_gate(n, addr) \
  set_gate (&idt_table[n], 15, 0,addr)

# define set_system_gate(n, addr) \
  set_gate (&idt_table[n], 15, 3, addr)

# define set_intr_gate(n, addr) \
  set_gate (&idt_table[n], 14, 0, addr)

# define CR0_PG (1 << 31)
# define CR0_WP (1 << 16)

static inline
void set_cr0(unsigned long val)
{
  __asm__ volatile ("mov %0,%%cr0\n\t": : "r" (val): "memory");
}

static inline
unsigned long get_cr0(void)
{
  unsigned long val;
  __asm__ volatile ("mov %%cr0,%0\n\t":"=&r" (val):);
  return val;
}

# define sti() __asm__ volatile ("sti": : :"memory")
# define cli() __asm__ volatile ("cli": : :"memory")
# define hlt() __asm__ volatile ("hlt\n")
# define save_flags(x)						\
  __asm__ volatile ("pushfl\n\t popl %0\n\t":"=g"(x)::"memory")
# define restore_flags(x) \
  __asm__ volatile ("pushl %0 \n\t popfl\n\t"::"g"(x):"memory")

#endif /* !_SYSTEM_H_ */
