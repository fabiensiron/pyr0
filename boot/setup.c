/*
 * File: setup.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: mostly arch-dependent setup
 */

#include <atomos/kernel.h>
#include <atomos/console.h>

#include <asm/processor.h>
#include <asm/system.h>

extern int sprintf(char *buf, const char *fmt, ...);
extern void trap_init ();
extern void init_IRQ ();
extern void mem_init (void);


/* little printf for boot */
#define LOG_BUFF_LEN 80
char log_buf[LOG_BUFF_LEN];

#define klog(str)    early_kdebug (str, LOG_BUFF_LEN)

# define early_printf(fmt, ...)			\
  do {						\
    sprintf(log_buf, fmt, ##__VA_ARGS__);	\
    klog(log_buf);				\
  } while(0)


void setup_kernel ()
{ 
  early_console_init ();

  early_printf ("Welcome in ATOMOS !\n");
  early_printf ("boot sequence ...");
  
  init_early_pagination ();
  
  cpu_init ();
  
  trap_init ();

  init_IRQ ();

  sti();

   /* init paging */
  
  /* keyboard -> chr_dev_init*/ 

  /* video -> chr_dev_init */

  mem_init ();

  load_stack_info();

  /* NOTE: stack reset, do nothing here */

  return start_kernel ();
}
