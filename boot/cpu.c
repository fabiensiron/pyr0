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

/*

static
void load_gdt () {

  tss_.debug_flag = 0;
  tss_.io_map = 0;
  tss_.ss0 = MAKE_SELECTOR(KERNEL_DATA_SEGMENT, 0, 0);
  tss_.esp0 = 0x200000;
  


  gdt_[NULL_SEGMENT] = (struct gdt_entry){ 0 };

  gdt_[KERNEL_CODE_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 0, 1);
  gdt_[KERNEL_DATA_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 0, 0); 
  gdt_[USER_CODE_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 3, 1);
  gdt_[USER_DATA_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 3, 0); 
  gdt_[TSS_SEGMENT] = ADD_TSS_ENTRY ((t_uint32)&tss_, sizeof(struct tss_entry));

  struct desc_gdt gdt_desc;
  gdt_desc.limit = sizeof (gdt_) -1;
  gdt_desc.base = (t_uint32)gdt_;
  
  __asm__ volatile (
    "lgdt %0\n":: "m" (gdt_desc): "memory");
}

static
void load_tss ()
{
  __asm__ volatile (
    "movw $0x28, %%ax \n\
     ltr %%ax\n\
     movw %%ss, %0 \n\
     movl %%esp, %1\n"
      : "=m"(tss_.ss0) ,"=m"(tss_.esp0)
      :
      :
      );
}
*/

void load_final_stack ()
{
  
}

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

  
  //  load_sp(MAIN_KERNEL_STACK);
  //  reset_bp;
  /* load_stack_info(&tss) */

  /* set_tss_desc(t); */

  /* load_TR_desc */
  
}
