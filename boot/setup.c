/*
 * File: setup.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: mostly arch-dependent setup
 */

#include <atomos/kernel.h>
#include <atomos/console.h>
#include <asm/processor.h>

#define LOG_BUFF_LEN 80
#define klog(str)    early_kdebug (str, LOG_BUFF_LEN)

extern void trap_init ();
extern void init_IRQ ();

void setup_kernel ()
{ 
  early_console_init ();

  klog ("Welcome in ATOMOS ! \n");
  klog ("boot sequence...\n");
  
  init_early_pagination ();
  
  cpu_init ();
  
  load_stack_info ();

  trap_init ();

  init_IRQ ();

  __asm__ volatile ("sti\n");
  
  /* init physmem */

  /* init paging */
  
  /* keyboard -> chr_dev_init*/ 

  /* video -> chr_dev_init */

  return start_kernel ();
}
