/*
 * File: cpu.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: init the cpu (gdt, idt, tss ...)
 */

#include <atomos/kernel.h>
#include <asm/segment.h>
#include <asm/desc.h>
#include <asm/system.h>
#include <asm/processor.h>


struct desc_ptr idt_descr = { IDT_SIZE - 1, (u32) idt_table};

struct tss tss = { 0 };

struct gdt_struct gdt_entries =
  {
    .gdt =
    {
      [GDT_ENTRY_NULL] = { 0 },
      [GDT_ENTRY_KERNEL_CS] = GDT_ENTRY_INIT(0xc09a, 0, 0xfffff),
      [GDT_ENTRY_KERNEL_DS] = GDT_ENTRY_INIT(0xc092, 0, 0xfffff),
      [GDT_ENTRY_USER_CS] = GDT_ENTRY_INIT(0xc0fa, 0, 0xfffff),
      [GDT_ENTRY_USER_DS] = GDT_ENTRY_INIT(0xc0f2, 0, 0xfffff),
      [GDT_ENTRY_TSS] = { 0 }
    }
  };

void load_segments ()
{
  loadsegment_ds(__KERNEL_DS);
  loadsegment_es(__KERNEL_DS);
  loadsegment_fs(__KERNEL_DS);
  loadsegment_gs(__KERNEL_DS);
  loadsegment_ss(__KERNEL_DS);
  
  loadsegment_cs(__KERNEL_CS);
}

void gdt_init ()
{
 /* NOTE: thanks to multiboot, we are already in pm */
  struct desc_ptr gdt_descr;
    
  gdt_descr.ptr = (u32)&gdt_entries;
  gdt_descr.size = GDT_SIZE -1;
  load_gdt(&gdt_descr);


  /* reload segments */
  load_segments();
}

void cpu_init ()
{


  gdt_init ();

  load_idt(&idt_descr);

  /* set_tss_desc(t); */

  /* load_TR_desc */
  
  /* TODO: just before or the init of start_kernel, reload new stack to tss */
}
