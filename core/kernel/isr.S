/*
 * File: isr.S
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: handle irqs
 */

//	.irp 	id,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18
//	.globl _exception_\id
//	.endr	
	
/* Macros to handle context saving */	
	.macro SAVE_ALL
	pusha
	pushw %ds
	pushw %es
	pushw %fs
	pushw %gs
	pushl %ebx
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

	.macro ACK_1
	jmp 1f
1:	jmp 1f
1:	movb $0x20, %al
	outb %al, $0x20
	.endm

	.macro ACK_2
	jmp 1f
1:	jmp 1f
1:	movb $0x20, %al
	outb %al, $0xa0
	jmp 1f
1:	jmp 1f
1:	outb %al, $0x20
	.endm

.globl _bad_1_interrupt		
.globl _bad_2_interrupt
	
_bad_1_interrupt:
	SAVE_ALL
	ACK_1
	RESTORE_ALL

_bad_2_interrupt:
	SAVE_ALL
	ACK_2
	RESTORE_ALL

