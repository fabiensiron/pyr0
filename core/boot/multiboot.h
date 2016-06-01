#ifndef __MULTIBOOT_H__
#define __MULTIBOOT_H__

/* multiboot.h - the header for Multiboot */
/* Copyright (C) 1999  Free Software Foundation, Inc.
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */


/* Types.  */
#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

/* The Multiboot header.  */
typedef struct multiboot_header
{
	unsigned long magic;
	unsigned long flags;
	unsigned long checksum;
	unsigned long header_addr;
	unsigned long load_addr;
	unsigned long load_end_addr;
	unsigned long bss_end_addr;
	unsigned long entry_addr;
} multiboot_header_t;

/* The symbol table for a.out.  */
typedef struct aout_symbol_table
{
	unsigned long tabsize;
	unsigned long strsize;
	unsigned long addr;
	unsigned long reserved;
} aout_symbol_table_t;

/* The section header table for ELF.  */
typedef struct elf_section_header_table
{
	unsigned long num;
	unsigned long size;
	unsigned long addr;
	unsigned long shndx;
} elf_section_header_table_t;

/* The Multiboot information.  */
typedef struct multiboot_info
{
	unsigned long flags;
	unsigned long mem_lower;
	unsigned long mem_upper;
	unsigned long boot_device;
	unsigned long cmdline;
	unsigned long mods_count;
	unsigned long mods_addr;
	union
	{
		aout_symbol_table_t aout_sym;
		elf_section_header_table_t elf_sec;
	} u;
	unsigned long mmap_length;
	unsigned long mmap_addr;
	unsigned long drives_length;
	unsigned long drives_addr;
	unsigned long config_table;
	unsigned long boot_loader_name;
	unsigned long apm_table;
	unsigned long vbe_control_info;
	unsigned long vbe_mode_info;
} multiboot_info_t;

/* The module structure.  */
typedef struct module
{
	unsigned long mod_start;
	unsigned long mod_end;
	unsigned long string;
	unsigned long reserved;
} module_t;

typedef struct extmodule
{
	unsigned long addr;
	unsigned long len;
	char *name;
	char buf[64];
} extmodule_t;

/* The memory map. Be careful that the offset 0 is base_addr_low
   but no size.  */
typedef struct memory_map
{
	unsigned long size;
	unsigned long base_addr_low;
	unsigned long base_addr_high;
	unsigned long length_low;
	unsigned long length_high;
	unsigned long type;
} memory_map_t;

# define DRIVE_MODE_LBA 1
# define DRIVE_MODE_CHS 0

typedef struct drive
{
	unsigned long size;
	unsigned char drive_number;
	unsigned char drive_mode;
	unsigned short  drive_cylinders;
	unsigned char drive_heads;
	unsigned char drive_sectors;
	unsigned char drive_port1;
	unsigned char drive_port2;
	unsigned char drive_port3;
} drive_t;

struct  __attribute__ ((packed)) vbe_info_t {
	u16 attributes;
	u8  winA, winB;
	u16 granularity;
	u16 winsize;
	u16 segmentA, segmentB;
	u32 realFctPtr;
	u16 pitch;

	u16 Xres, Yres;
	u8  Wchar, Ychar, planes, bpp, banks;
	u8  memory_model, bank_size, image_pages;
	u8  reserved0;

	u8  red_mask, red_position;
	u8  green_mask, green_position;
	u8  blue_mask, blue_position;
	u8  rsv_mask, rsv_position;
	u8  directcolor_attributes;

	u32 physbase;
	u32 reserved1;
	u16 reserved2;
};

void dump_multiboot_info(multiboot_info_t *mbi);

#endif /* __MULTIBOOT_H__ */
