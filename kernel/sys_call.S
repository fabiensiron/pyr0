/*
 * File: sys_call.S
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: Syscall entry and interrupt subroutines (ISR)
 */

	.irp 	id,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18
	.globl _exception_\id
	.endr	
	
/* Macros to handle context saving */	
	.macro SAVE_ALL
	pusha
	pushw %ds
	pushw %es
	pushw %fs
	pushw %ebx
	mov $0x10, %bx
	mov %bx, %ds
	mov %bx, %es
	mov %bx, %fs
	mov %bx, %gs
	popl %ebx
	.endm

	.macro RESTORE_ALL
	popw %gs
	popw %fs
	popw %es
	popw %ds
	popa
	.endm
	

/* exception isr */
	.extern debug_trap

	.irp	id,0,1,2,3,4,5,6,7,9,15,16,17,18
_exception_\id:
	pushl $debug_trap
	pushl $\id
	jmp no_error_code
	.endr

	.irp 	id,10,11,12,13,14
_exception_\id:
	pushl $debug_trap
	pushl $\id
	jmp error_code
	.endr
	
_exception_8:
	jmp 1f
1:	hlt
	jmp 1b

no_error_code:
	xchgl %ecx, (%esp)
	xchgl %eax, 4(%esp) // BUG: eax and ecx are not saved
	SAVE_ALL
	pushl $42 // fake error code
	pushl %ecx
	call *%eax
	addl $8, %esp
	RESTORE_ALL
	iret

error_code:
	xchgl %ebx,8(%esp)
	xchgl %eax,4(%esp)
	xchgl %ecx,(%esp)
	SAVE_ALL
	pushl %ebx
	pushl %ecx
	call *%eax
	addl $8,%esp
	RESTORE_ALL
	iret
