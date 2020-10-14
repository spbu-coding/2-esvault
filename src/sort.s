	.file	"sort.c"
	.text
	.p2align 4
	.globl	swap
	.def	swap;	.scl	2;	.type	32;	.endef
	.seh_proc	swap
swap:
	.seh_endprologue
	movl	(%rcx), %eax
	movl	(%rdx), %r8d
	movl	%r8d, (%rcx)
	movl	%eax, (%rdx)
	ret
	.seh_endproc
	.p2align 4
	.globl	sort_array
	.def	sort_array;	.scl	2;	.type	32;	.endef
	.seh_proc	sort_array
sort_array:
	.seh_endprologue
	movq	%rcx, %r9
	movq	%rdx, %r10
	cmpq	$1, %rdx
	jbe	.L3
	movq	%rcx, %r8
	movl	$1, %r11d
	.p2align 4,,10
	.p2align 3
.L5:
	movq	%r11, %rax
	.p2align 4,,10
	.p2align 3
.L7:
	movl	(%r8), %edx
	movl	(%r9,%rax,4), %ecx
	cmpl	%ecx, %edx
	jle	.L6
	movl	%ecx, (%r8)
	movl	%edx, (%r9,%rax,4)
.L6:
	addq	$1, %rax
	cmpq	%rax, %r10
	ja	.L7
	addq	$1, %r11
	addq	$4, %r8
	cmpq	%r11, %r10
	jne	.L5
.L3:
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 10.2.0"
