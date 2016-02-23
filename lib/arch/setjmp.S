// 
// File: setjmp.S
// Source: linux
//
// jmp_buf format and offset:
// 	%ebx:  0
// 	%esp:  4
//	%ebp:  8
//	%esi:  12
//	%edi:  16
// 	<ret>: 20
// 
	
	.globl setjmp
setjmp:
	movl 4(%esp),%edx
	popl %ecx
	xorl %eax, %eax
	movl %ebx, (%edx)
	movl %esp, 4(%edx)
	pushl %ecx
	movl %ebp,8(%edx)
	movl %esi,12(%edx)
	movl %edi,16(%edx)
	movl %ecx,20(%edx)
	ret

	.globl longjmp
longjmp:
	movl 4(%esp),%edx
	movl 8(%esp),%eax
	movl (%edx),%ebx
	movl 4(%edx),%esp
	movl 8(%edx),%ebp
	movl 12(%edx),%esi
	movl 16(%edx),%edi
	jmp *20(%edx)
