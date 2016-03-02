#define MAGIC 0x1badb002
#define FLAGS 0x07
#define EARLY_STACK_SIZE 0x8000

	.extern init_early_pagination
	.extern setup_kernel

.section .multiboot
	.align 4
multiboot_header:
	.long MAGIC
	.long FLAGS
	.long -(MAGIC + FLAGS)
	.long multiboot_header
	.long __begin_kernel
	.long __end_load
	.long __end_kernel

.global kernel_entry
kernel_entry:
	cli
	
	movl $(_ebss+EARLY_STACK_SIZE), %esp
	movl $0, %ebp

	pushl $0
	popf

	push %ebx /* multiboot_info_t */
	push %eax /* magic */

	lea setup_kernel, %ecx
	call *%ecx
	
  /* because I'm paranoid */
loop:
	hlt
	jmp loop

//.comm stack, EARLY_STACK_SIZE
