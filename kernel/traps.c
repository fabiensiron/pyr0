/*
 * File: traps.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: stuff about traps
 */

# include <asm/segment.h>
/* TODO: switch to <asm/irq_vectors.h> */
# include <asm/system.h>
# include <asm/desc.h>

# include <atomos/console.h>

struct gate_desc idt_table[IDT_ENTRIES] = { 0, };

void debug_trap (void)
{
  early_kdebug ("trap test\n", 50);
  __asm__ ("hlt\n");
}

# define EXCEPT_DEF(X) void _exception_##X(void)
#  include "traps.def"
# undef EXCEPT_DEF

void trap_init (void)
{
  int i;
  
  set_trap_gate (0, &_exception_0);
  set_trap_gate (1, &_exception_1);
  set_trap_gate (2, &_exception_2);
  set_system_gate (3, &_exception_3);
  set_system_gate (4, &_exception_4);
  set_system_gate (5, &_exception_5);
  set_trap_gate (6, &_exception_6);
  set_trap_gate (7, &_exception_7);
  set_trap_gate (8, &_exception_8);
  set_trap_gate (9, &_exception_9);
  set_trap_gate (10, &_exception_10);
  set_trap_gate (11, &_exception_11);
  set_trap_gate (12, &_exception_12);
  set_trap_gate (13, &_exception_13);
  set_trap_gate (14, &_exception_14);
  set_trap_gate (15, &_exception_15);
  set_trap_gate (16, &_exception_16);  
  for (i = 17; i < 32; i++)
    set_trap_gate (i, &_exception_17);    
}
  
