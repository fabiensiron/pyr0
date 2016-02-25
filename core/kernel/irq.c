/*
 * File: irq.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *         but the code comes mostly from linux
 *
 * Description: handle interrupt requests (irq) stuff
 *
 */

# include <asm/io.h>
# include <asm/system.h>
# include <asm/desc.h>
# include <asm/irq.h>

# include <atomos/kernel.h>

extern struct gate_desc idt_table[IDT_ENTRIES];

# define PIC_MASTER 0x20
# define PIC_SLAVE  0xa0

static unsigned char cache_21 = 0xff;
static unsigned char cache_a1 = 0xff;

static inline void mask_irq(unsigned int nr)
{
  unsigned char mask;

  mask = 1 << (nr & 7);

  if (nr < 8)
    {
      cache_21 |= mask;
      outb(PIC_MASTER+1, cache_21);
    }
  else
    {
      cache_a1 |= mask;
      outb(PIC_SLAVE + 1, cache_a1);
    }
}

static inline void unmask_irq(unsigned int nr)
{
  unsigned char mask;

  mask = ~(1 << (nr & 7));
  if (nr < 8)
    {
      cache_21 &= mask;
      outb(PIC_MASTER+1, cache_21);
    }
  else
    {
      cache_a1 &= mask;
      outb(PIC_SLAVE+1, cache_a1);
    }
}

void disable_irq(unsigned int irq_)
{
  unsigned long flags;

  save_flags(flags);
  cli();
  mask_irq(irq_);
  restore_flags(flags);
}

void enable_irq(unsigned int irq_)
{
  unsigned long flags;

  save_flags(flags);
  cli();
  unmask_irq(irq_);
  restore_flags(flags);
}

static void (*bad_interrupt[16])(void) =
{
  _bad_1_interrupt,  _bad_1_interrupt,
  _bad_1_interrupt,  _bad_1_interrupt,
  _bad_1_interrupt,  _bad_1_interrupt,
  _bad_1_interrupt,  _bad_1_interrupt,
  _bad_2_interrupt,  _bad_2_interrupt,  
  _bad_2_interrupt,  _bad_2_interrupt,    
  _bad_2_interrupt,  _bad_2_interrupt,    
  _bad_2_interrupt,  _bad_2_interrupt
};

static void (*isr[16])(void) =
{
  _irq_0, _irq_1, _irq_2,  _irq_3,  _irq_4,  _irq_5,  _irq_6,  _irq_7,
  _irq_8, _irq_9, _irq_10, _irq_11, _irq_12, _irq_13, _irq_14, _irq_15,  
};

static void (*interrupt[16])(void) =
{
  0,
};

int setup_irq(unsigned int irq, void (*handler)(void))
{
  unsigned long flags;
  
  if (irq > 15)
    return -1;
  if (!handler)
    return -1;

  interrupt[irq] = handler;

  save_flags(flags);
  cli();
  set_intr_gate(0x20+irq, isr[irq]);
  sti();
  restore_flags(flags);

  enable_irq(0);
  
  return 0;
}

void free_irq(unsigned int irq)
{
  unsigned long flags;

  if (irq > 15)
    return;

  disable_irq(0);

  save_flags(flags);
  cli();
  set_intr_gate(0x20+irq,bad_interrupt[irq]);
  sti();
  restore_flags(flags);
}

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

void do_IRQ(int irq)
{
  cli();
  interrupt[irq]();
  sti();
}

extern void pit_init();

void init_IRQ(void)
{
  int i;
  
  pic_init ();

  for (i = 0; i< 16; i++)
    set_intr_gate(0x20+i, bad_interrupt[i]);

  pit_init();
}
