/*
 * File: processor.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: processor init (gdt, idt, tss ...)
 */

#ifndef _PROCESSOR_H_
# define _PROCESSOR_H_

# include <kernel/types.h>
# include <asm/system.h>

struct tss
{
  u16 previous_task, unusedt;
  u32 esp0;
  u16 ss0, unused0;
  u32 esp1;
  u16 ss1, unused1;
  u32 esp2;
  u16 ss2, unused2;
  u32 cr3;
  u32 eip,eflags;
  u32 eax,ecx,edx,ebx,esp,ebp,esi,edi;
  u16 es, unused_es;
  u16 cs, unused_cs;
  u16 ss, unused_ss;
  u16 ds, unused_ds;
  u16 fs, unused_fs;
  u16 gs, unused_gs;
  u16 ldt_selector, unused_ldt;
  u16 debug_flag, io_map;
};

void cpu_init (void);
void init_early_pagination (void);

# define load_sp(v) __asm__ volatile("movl %0, %%esp"::"i"(v):)
# define reset_bp __asm__ volatile("movl $0, %%ebp":);

static inline void load_stack_info () __attribute__((always_inline));

void load_stack_info (void)
{
  load_sp(MAIN_KERNEL_STACK);
  reset_bp;
}

# define load_stack_info2			\
  load_sp(MAIN_KERNEL_STACK);			\
  reset_bp


#endif /* !_PROCESSOR_H_ */
