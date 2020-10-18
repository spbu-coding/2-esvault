	.file	"sort.c"
	.text
	.p2align 4
	.globl	sort_array
	.type	sort_array, @function
sort_array:
        lea     r9d, [rsi-1]
        xor     r8d, r8d
        test    esi, esi
        jle     .L11
.L5:
        mov     ecx, DWORD PTR [rdi+r8*4]
        mov     rax, r8
.L4:
        mov     edx, DWORD PTR [rdi+rax*4]
        cmp     edx, ecx
        jge     .L3
        mov     DWORD PTR [rdi+rax*4], ecx
        mov     ecx, edx
        mov     DWORD PTR [rdi+r8*4], edx
.L3:
        add     rax, 1
        cmp     esi, eax
        jg      .L4
        lea     rax, [r8+1]
        cmp     r8, r9
        je      .L12
        mov     r8, rax
        jmp     .L5
.L12:
        ret
.L11:
        ret
