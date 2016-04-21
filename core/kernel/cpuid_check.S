//  Basically, we try to change id bit, if it remains the same, cpu
//  does not support cpuid instruction.
//
//  @ret: 0, cpu does not have cpuid, otherwise, it's okay.


.section .text
.align 4

.set id, 0x00200000

.global cpuid_check
.type cpuid_check, @function

cpuid_check:
	pushf
	pushf
	xorl $id,(%esp)
	popf
	pushf
	pop %eax
	xor (%esp),%eax
	popf
	andl $id,%eax
	ret

.global cpuid_extended_check
.type cpuid_extended_check, @function

cpuid_extended_check:
	movl $0x80000000, %eax
	cpuid
	cmpl $0x80000004, %eax
	jl fail
	movl $1, %eax
	ret
fail:
	movl $0, %eax
	ret

