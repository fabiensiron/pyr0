/*
 * File: irq.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: handle interrupt requests (irq) stuff
 */

# include <asm/io.h>
# include <asm/system.h>
# include <asm/desc.h>

# include <atomos/kernel.h>

extern struct gate_desc idt_table[IDT_ENTRIES];

# define PIC_MASTER 0x20
# define PIC_SLAVE  0xa0

void pic_init (void)
{
  /* cascaded and front edge */
  outb(PIC_MASTER, 0x11);
  outb(PIC_SLAVE, 0x11);

  /* master_offset idt-> 32 slave_offset idt -> 40 */
  outb(PIC_MASTER+1, 0x20);
  outb(PIC_SLAVE+1, 0x28);

  /* master/slave connection */
  outb(PIC_MASTER+1, 0x4);
  outb(PIC_SLAVE+1, 0x2);

  /* icw4 default mode */
  outb(PIC_MASTER+1, 0x1);
  outb(PIC_SLAVE+1, 0x1);

  /* ocw1 masking */
  outb(PIC_MASTER+1, 0xfb);
  outb(PIC_SLAVE+1, 0xff);
}

void init_IRQ(void)
{
  int i;
  
  pic_init ();

  for (i = 0; i< 16; i++)
    set_intr_gate(0x20+i, NULL);
}
