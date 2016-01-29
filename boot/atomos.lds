OUTPUT_FORMAT("elf32-i386")
OUTPUT_ARCH("i386")
ENTRY(kernel_entry)

SECTIONS
{
	. = 0x100000;
	__begin_load = .;

	.multiboot :
	{
		*(.multiboot);
		LONG(0);
	}

	__begin_kernel = .;
	
  	.text : 
  	{
		*(.text*)  
		PROVIDE(_etext = .);
  	}

  	.rodata :
  	{ 
		*(.rodata*)
		PROVIDE(_erodata = .);
  	}

  	.data :
  	{
    	  	*(.data)
		PROVIDE(_edata = .);
  	}

	__end_load = .;

	.bss :
	{
		*(COMMON)	
		*(.bss)
		PROVIDE(_ebss = .);
		*(.stack)
		. += 0x4000;
	}

	__end_kernel = .;
	
	/DISCARD/ :
	{
		*(.note*)	
		*(.indent)
		*(.comment)
		*(.stab)
		*(.stabstr)
	}
}
