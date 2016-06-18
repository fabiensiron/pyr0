/*
 * File main.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: setup the operating system (mostly non arch-dependent)
 */
#include <kernel/pyr0.h>
#include <kernel/console.h>
#include <kernel/mm.h>
#include <kernel/kmalloc.h>
#include <kernel/mman.h>
#include <kernel/serial.h>
#include <kernel/tty.h>
#include <kernel/cpuinfo.h>
#include <kernel/cmdline.h>

#include <asm/system.h>
#include <asm/pgtable.h>

#include "../boot/multiboot.h"

extmodule_t boot_module;

void start_kernel(multiboot_info_t *info)
{
	unsigned long long int i;
	struct runtime_opt opts;

	early_printk("start kernel ...\n");

	assert(info->flags & (1 << 6));

	memory_map_t *mmap = (void *)info->mmap_addr;

	while ((u32)mmap < info->mmap_addr + info->mmap_length)
	{
		if (mmap->type == 2)
		{
			for (i = 0; i < mmap->length_low; i += 0x1000)
			{
				if (mmap->base_addr_high > 0) continue;
				frame_ref_once ((mmap->base_addr_low + i) & PAGE_MASK);
			}
		}
		mmap = (memory_map_t *)((u32)mmap + mmap->size + sizeof(u32));
	}

	/* mem/paging */
	if (paging_init())
		panic("Fatal error: memory cannot be mapped\n");

	console_init();
	tty_init();

	kmalloc_init();

	cpuinfo_dump();

	cmdline_fill_opts(&opts);

	printk(KERN_INFO, "Core boot process done\n");

	if (info->mods_count == 0)
		start_runtime(NULL, 0, NULL, &opts);
	else
		start_runtime((void *)boot_module.addr,
			      (long)boot_module.len,
			      boot_module.name, &opts);

	for (;;)
		;
}
