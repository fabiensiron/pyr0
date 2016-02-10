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

#include <atomos/mm.h>
#include <atomos/page.h>
#include <asm/pgtable.h>

#include "multiboot.h"

extern int sprintf(char *buf, const char *fmt, ...);
extern void trap_init ();
extern void init_IRQ ();


/* little printf for boot */
#define LOG_BUFF_LEN 80
char log_buf[LOG_BUFF_LEN];

#define klog(str)    early_kdebug (str, LOG_BUFF_LEN)

# define early_printf(fmt, ...)			\
  do {						\
    sprintf(log_buf, fmt, ##__VA_ARGS__);	\
    klog(log_buf);				\
  } while(0)

/* til' we don't have a real printk, we can't call panic */
static 
void die (const char *msg)
{
  early_printf ("\n#########################\n");
  early_printf ("######### PANIC #########\n");
  early_printf ("#########################\n\n");
  early_printf ("  Error: %s\n", msg);
  early_printf ("  Halt processor...\n");

  hlt();
}

void setup_kernel (unsigned long magic, multiboot_info_t *info)
{ 
  early_console_init ();

  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    die ("Wrong bootloader");

  early_printf ("Welcome in ATOMOS !\n");
  early_printf ("boot sequence ...\n");

  init_early_pagination ();
  
  cpu_init ();
  
  trap_init ();

  init_IRQ ();

  sti();
  /* here we should maybe switch to start_kernel */

  if (!(info->flags & (1 << 6)))
      die ("Memory map unavailable !\n");

  u32 nr_frames = frame_allocator_init(info->mem_upper * 1024);

  early_printf("Memory init %x frames\n", nr_frames);

  //  load_stack_info(); // FIXME

  /* NOTE: stack reset, do nothing here */

  return start_kernel (info);
}
