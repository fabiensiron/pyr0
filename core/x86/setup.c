/*
 * File: setup.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: mostly arch-dependent setup
 */

#include <kernel/pyr0.h>
#include <kernel/console.h>
#include <kernel/serial.h>
#include <kernel/cmdline.h>
#include <kernel/snd.h>

#include <asm/processor.h>
#include <asm/system.h>
#include <asm/pgtable.h>

#include <kernel/mm.h>
#include <kernel/page.h>

#include <string.h>

#include "../boot/multiboot.h"

extern extmodule_t boot_module;

extern void trap_init ();
extern void init_IRQ ();

void setup_kernel (multiboot_info_t *info, unsigned long magic)
{
	serial_early_init();

	assert(magic == MULTIBOOT_BOOTLOADER_MAGIC);

	init_early_pagination ();

	cpu_init ();

	trap_init ();

	init_IRQ ();

	sti();

	beep();

	size_t cmdline_len = strlen((char *)info->cmdline);
	cmdline_parse((char *)info->cmdline, cmdline_len);

	/* okay, this is a *ugly* hack, but it works if there is only 1 module */
	if (info->mods_count != 0)
	{
		boot_module.addr = 0x4000;
		boot_module.len =
			((module_t *)info->mods_addr)->mod_end -
			((module_t *)info->mods_addr)->mod_start;
		/* set name to buf */
		boot_module.name = (char *)&boot_module.buf;

		memcpy(&boot_module.buf,(void *)(((module_t *)info->mods_addr)->string + sizeof(long)),64);

		memcpy((void*)0x4000,(void *)((module_t *)info->mods_addr)->mod_start, PAGE_SIZE);
	}

	u32 nr_frames = frame_allocator_init(info->mem_upper * 1024);

	//  load_stack_info(); // FIXME

	/* NOTE: stack reset, do nothing here */

	return start_kernel (info);
}
