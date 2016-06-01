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
	
.extern do_IRQ
	.macro IRQ num chip
.globl _irq_\num
_irq_\num:
	SAVE_ALL
	ACK_\chip
	pushl $\num
	call do_IRQ
	add $4, %esp
	RESTORE_ALL
	iret
	.endm

	IRQ 0, 1
	IRQ 1, 1
	IRQ 2, 1
	IRQ 3, 1
	IRQ 4, 1
	IRQ 5, 1
	IRQ 6, 1
	IRQ 7, 1
	IRQ 8,  2
	IRQ 9,  2
	IRQ 10, 2
	IRQ 11, 2
	IRQ 12, 2
	IRQ 13, 2
	IRQ 14, 2
	IRQ 15, 2
