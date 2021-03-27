rec_mul:
        push    r15
        push    r14
        push    r13
        push    r12
        mov     r12d, edx
        push    rbp
        push    rbx
        sub     rsp, 40
        cmp     edi, esi
        je      .L26
        mov     r15d, DWORD PTR used[rip]
        movsx   rdx, esi
        mov     ebp, esi
        lea     eax, [r15+1]
        mov     DWORD PTR [rsp+28], r15d
        mov     DWORD PTR used[rip], eax
        movsx   rax, edi
        lea     r13, [rax+rax*4]
        add     r13, rdx
        xor     edx, edx
        mov     esi, DWORD PTR orderings[0+r13*4]
        call    rec_mul
        mov     edi, DWORD PTR orderings[0+r13*4]
        mov     esi, ebp
        mov     edx, 1
        mov     ebx, eax
        add     edi, 1
        call    rec_mul
        mov     esi, 1
        movsx   rcx, r15d
        test    r12d, r12d
        movsx   rdx, eax
        movsx   rax, ebx
        mov     r15d, esi
        mov     r14d, DWORD PTR x[0+rax*4]
        mov     ebx, DWORD PTR y[0+rdx*4]
        cmovne  esi, r14d
        cmove   r15d, ebx
        mov     DWORD PTR y[0+rcx*4], ebx
        mov     r10d, DWORD PTR y[0+rax*4]
        mov     DWORD PTR x[0+rcx*4], r14d
        imul    rax, rax, 8000000
        movsx   rbp, esi
        lea     rdi, arr[rax]
        imul    rax, rcx, 8000000
        mov     QWORD PTR [rsp+8], rax
        test    r14d, r14d
        jle     .L1
        imul    rdx, rdx, 8000000
        movsx   r11, r10d
        xor     r13d, r13d
        xor     r12d, r12d
        sal     r11, 3
        sal     rbp, 3
        sub     r10d, 1
        lea     rax, arr[rdx]
        mov     QWORD PTR [rsp+16], rax
.L14:
        test    ebx, ebx
        jle     .L9
        mov     rsi, QWORD PTR [rsp+8]
        movsx   rax, r13d
        xor     r9d, r9d
        lea     r8, arr[rsi+rax*8]
        mov     rsi, QWORD PTR [rsp+16]
.L10:
        movsx   rax, r10d
        xor     ecx, ecx
        test    r10d, r10d
        je      .L13
.L11:
        mov     rdx, QWORD PTR [rdi+rax*8]
        imul    rdx, QWORD PTR [rsi+rax*8]
        sub     rax, 1
        add     rcx, rdx
        test    eax, eax
        jne     .L11
.L13:
        mov     rax, QWORD PTR [rdi]
        imul    rax, QWORD PTR [rsi]
        add     r9d, 1
        add     rsi, r11
        add     rcx, rax
        add     QWORD PTR [r8], rcx
        add     r8, rbp
        cmp     ebx, r9d
        jne     .L10
.L9:
        add     r12d, 1
        add     rdi, r11
        add     r13d, r15d
        cmp     r14d, r12d
        jne     .L14
.L1:
        mov     eax, DWORD PTR [rsp+28]
        add     rsp, 40
        pop     rbx
        pop     rbp
        pop     r12
        pop     r13
        pop     r14
        pop     r15
        ret
.L26:
        mov     DWORD PTR [rsp+28], edi
        cmp     edx, 1
        jne     .L1
        mov     ebx, DWORD PTR used[rip]
        movsx   rcx, edi
        mov     edx, DWORD PTR x[0+rcx*4]
        lea     eax, [rbx+1]
        mov     DWORD PTR [rsp+28], ebx
        mov     DWORD PTR used[rip], eax
        movsx   rax, ebx
        mov     DWORD PTR x[0+rax*4], edx
        mov     edx, DWORD PTR y[0+rcx*4]
        mov     ebx, DWORD PTR x[0+rcx*4]
        mov     DWORD PTR y[0+rax*4], edx
        test    ebx, ebx
        jle     .L1
        movsx   rbp, DWORD PTR y[0+rcx*4]
        imul    rax, rax, 8000000
        movsx   rdi, ebx
        xor     r10d, r10d
        imul    rcx, rcx, 8000000
        sal     rdi, 3
        mov     r11, rbp
        sal     rbp, 3
        lea     r9, arr[rax]
        lea     r8d, [r11-1]
.L5:
        mov     rdx, r9
        xor     eax, eax
        test    r11d, r11d
        jle     .L7
.L6:
        mov     rsi, QWORD PTR arr[rcx+rax*8]
        mov     QWORD PTR [rdx], rsi
        mov     rsi, rax
        add     rdx, rdi
        add     rax, 1
        cmp     r8, rsi
        jne     .L6
.L7:
        add     r10d, 1
        add     r9, 8
        add     rcx, rbp
        cmp     ebx, r10d
        jne     .L5
        jmp     .L1
used:
        .long   5
cost:
        .zero   200
arr:
        .zero   120000000
orderings:
        .zero   100
y:
        .zero   60
x:
        .zero   60
n:
        .zero   4