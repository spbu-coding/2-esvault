	.file	"sort.c"
	.text
	.p2align 4,,15
	.globl	swap
	.type	swap, @function
swap:
.LFB0:
	.cfi_startproc
	movl	(%rdi), %eax
	movl	(%rsi), %edx
	movl	%edx, (%rdi)
	movl	%eax, (%rsi)
	ret
	.cfi_endproc
.LFE0:
	.size	swap, .-swap
	.p2align 4,,15
	.globl	sort_array
	.type	sort_array, @function
sort_array:
.LFB1:
	.cfi_startproc
	testl	%esi, %esi
	jle	.L3
	leal	-1(%rsi), %r11d
	movl	$1, %r9d
	addq	$4, %rdi
	movq	%rdi, %r8
	leal	-2(%rsi), %r10d
	addq	$1, %r11
	cmpq	%r11, %r9
	je	.L3
	.p2align 4,,10
	.p2align 3
.L9:
	movl	%r10d, %eax
	addq	%r9, %rax
	leaq	(%rdi,%rax,4), %rsi
	movq	%r8, %rax
	.p2align 4,,10
	.p2align 3
.L6:
	movl	-4(%r8), %edx
	movl	(%rax), %ecx
	cmpl	%ecx, %edx
	jle	.L5
	movl	%ecx, -4(%r8)
	movl	%edx, (%rax)
.L5:
	addq	$4, %rax
	cmpq	%rsi, %rax
	jne	.L6
	addq	$1, %r9
	addq	$4, %r8
	subl	$1, %r10d
	cmpq	%r11, %r9
	jne	.L9
.L3:
	rep ret
	.cfi_endproc
.LFE1:
	.size	sort_array, .-sort_array
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
