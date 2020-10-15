	.file	"sort.c"
	.text
	.p2align 4
	.globl	swap
	.type	swap, @function
swap:
.LFB0:
	.cfi_startproc
	endbr64
	movl	(%rdi), %eax
	movl	(%rsi), %edx
	movl	%edx, (%rdi)
	movl	%eax, (%rsi)
	ret
	.cfi_endproc
.LFE0:
	.size	swap, .-swap
	.p2align 4
	.globl	sort_array
	.type	sort_array, @function
sort_array:
.LFB1:
	.cfi_startproc
	endbr64
	cmpq	$1, %rsi
	jbe	.L3
	movq	%rdi, %r8
	movl	$1, %r9d
	.p2align 4,,10
	.p2align 3
.L5:
	movq	%r9, %rax
	.p2align 4,,10
	.p2align 3
.L7:
	movl	(%r8), %edx
	movl	(%rdi,%rax,4), %ecx
	cmpl	%ecx, %edx
	jle	.L6
	movl	%ecx, (%r8)
	movl	%edx, (%rdi,%rax,4)
.L6:
	addq	$1, %rax
	cmpq	%rax, %rsi
	ja	.L7
	addq	$1, %r9
	addq	$4, %r8
	cmpq	%r9, %rsi
	jne	.L5
.L3:
	ret
	.cfi_endproc
.LFE1:
	.size	sort_array, .-sort_array
	.ident	"GCC: (Ubuntu 9.3.0-10ubuntu2) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
