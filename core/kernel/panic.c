/*
 * File: panic.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <kernel/pyr0.h>

#include <asm/system.h>

extern int tty_is_init;
static int has_panicked;

void panic(const char *s)
{
	if (has_panicked)
		goto loop;

	has_panicked = 1;

	cli();

	if (!tty_is_init)
	{
		early_printk("### KERNEL PANIC: ###\n");
		early_printk(s);
	}
	else
	{
		printk(KERN_ERR, "### KERNEL PANIC: ###\n");
		printk(KERN_ERR, s);
	}

loop:
	for (;;)
		;
}
