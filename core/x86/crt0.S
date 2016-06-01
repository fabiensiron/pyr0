#define EARLY_STACK_SIZE 0x8000
	.set ALIGN, 1 << 0
	.set MEMINFO, 1 << 1
	.set VIDINFO, 1 << 2
	.set FLAGS, ALIGN | MEMINFO | VIDINFO

	.set MAGIC,  0x1BADB002
	.set CHECKSUM,  -(MAGIC+FLAGS)

	.extern init_early_pagination
	.extern setup_kernel

.section .multiboot
	.align 4
	.long MAGIC
	.long FLAGS
	.long CHECKSUM
	.long 0, 0, 0, 0, 0
	
	.long 0x00000000
	.long 0
	.long 0
	.long 0

.section .text

.global kernel_entry
kernel_entry:
	cli
	
	movl $(_ebss+EARLY_STACK_SIZE), %esp
	and $-16, %esp
	movl $0, %ebp

	pushl $0
	popf

	pushl %eax /* multiboot_info_t */
	pushl %ebx /* magic */
	
	call setup_kernel
	addl $4, %esp
	
  /* because I'm paranoid */
loop:
	hlt
	jmp loop

//.comm stack, EARLY_STACK_SIZE
