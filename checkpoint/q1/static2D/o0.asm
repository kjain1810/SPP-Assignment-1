n:
        .zero   4
x:
        .zero   60
y:
        .zero   60
orderings:
        .zero   100
arr:
        .zero   120000000
cost:
        .zero   200
used:
        .long   5
rec_mul:
        push    rbp
        mov     rbp, rsp
        push    r15
        push    r14
        push    r13
        push    r12
        push    rbx
        sub     rsp, 56
        mov     DWORD PTR [rbp-84], edi
        mov     DWORD PTR [rbp-88], esi
        mov     DWORD PTR [rbp-92], edx
        mov     eax, DWORD PTR [rbp-84]
        cmp     eax, DWORD PTR [rbp-88]
        jne     .L2
        mov     ebx, DWORD PTR [rbp-84]
        cmp     DWORD PTR [rbp-92], 1
        jne     .L3
        mov     eax, DWORD PTR used[rip]
        lea     edx, [rax+1]
        mov     DWORD PTR used[rip], edx
        mov     ebx, eax
        mov     eax, DWORD PTR [rbp-84]
        cdqe
        mov     edx, DWORD PTR x[0+rax*4]
        movsx   rax, ebx
        mov     DWORD PTR x[0+rax*4], edx
        mov     eax, DWORD PTR [rbp-84]
        cdqe
        mov     edx, DWORD PTR y[0+rax*4]
        movsx   rax, ebx
        mov     DWORD PTR y[0+rax*4], edx
        mov     r13d, 0
        jmp     .L4
.L7:
        mov     eax, DWORD PTR [rbp-84]
        cdqe
        mov     eax, DWORD PTR y[0+rax*4]
        imul    eax, r13d
        mov     r14d, eax
        mov     r12d, 0
        jmp     .L5
.L6:
        lea     edx, [r14+r12]
        mov     eax, DWORD PTR [rbp-84]
        cdqe
        mov     eax, DWORD PTR x[0+rax*4]
        imul    eax, r12d
        lea     ecx, [r13+0+rax]
        movsx   rdx, edx
        mov     eax, DWORD PTR [rbp-84]
        cdqe
        imul    rax, rax, 1000000
        add     rax, rdx
        mov     rax, QWORD PTR arr[0+rax*8]
        movsx   rcx, ecx
        movsx   rdx, ebx
        imul    rdx, rdx, 1000000
        add     rdx, rcx
        mov     QWORD PTR arr[0+rdx*8], rax
        add     r12d, 1
.L5:
        mov     eax, DWORD PTR [rbp-84]
        cdqe
        mov     eax, DWORD PTR y[0+rax*4]
        cmp     r12d, eax
        jl      .L6
        add     r13d, 1
.L4:
        mov     eax, DWORD PTR [rbp-84]
        cdqe
        mov     eax, DWORD PTR x[0+rax*4]
        cmp     r13d, eax
        jl      .L7
.L3:
        mov     eax, ebx
        jmp     .L8
.L2:
        mov     eax, DWORD PTR used[rip]
        lea     edx, [rax+1]
        mov     DWORD PTR used[rip], edx
        mov     DWORD PTR [rbp-68], eax
        mov     eax, DWORD PTR [rbp-88]
        movsx   rcx, eax
        mov     eax, DWORD PTR [rbp-84]
        movsx   rdx, eax
        mov     rax, rdx
        sal     rax, 2
        add     rax, rdx
        add     rax, rcx
        mov     ecx, DWORD PTR orderings[0+rax*4]
        mov     eax, DWORD PTR [rbp-84]
        mov     edx, 0
        mov     esi, ecx
        mov     edi, eax
        call    rec_mul
        mov     DWORD PTR [rbp-72], eax
        mov     eax, DWORD PTR [rbp-88]
        movsx   rcx, eax
        mov     eax, DWORD PTR [rbp-84]
        movsx   rdx, eax
        mov     rax, rdx
        sal     rax, 2
        add     rax, rdx
        add     rax, rcx
        mov     eax, DWORD PTR orderings[0+rax*4]
        lea     ecx, [rax+1]
        mov     eax, DWORD PTR [rbp-88]
        mov     edx, 1
        mov     esi, eax
        mov     edi, ecx
        call    rec_mul
        mov     DWORD PTR [rbp-76], eax
        mov     eax, DWORD PTR [rbp-72]
        cdqe
        mov     edx, DWORD PTR x[0+rax*4]
        mov     eax, DWORD PTR [rbp-68]
        cdqe
        mov     DWORD PTR x[0+rax*4], edx
        mov     eax, DWORD PTR [rbp-68]
        cdqe
        mov     esi, DWORD PTR x[0+rax*4]
        mov     eax, DWORD PTR [rbp-76]
        cdqe
        mov     edx, DWORD PTR y[0+rax*4]
        mov     eax, DWORD PTR [rbp-68]
        cdqe
        mov     DWORD PTR y[0+rax*4], edx
        mov     eax, DWORD PTR [rbp-68]
        cdqe
        mov     eax, DWORD PTR y[0+rax*4]
        mov     r8d, eax
        mov     eax, DWORD PTR [rbp-72]
        cdqe
        mov     r12d, DWORD PTR y[0+rax*4]
        mov     DWORD PTR [rbp-52], 1
        mov     DWORD PTR [rbp-56], 1
        cmp     DWORD PTR [rbp-92], 0
        je      .L9
        mov     DWORD PTR [rbp-56], esi
        jmp     .L10
.L9:
        mov     eax, r8d
        mov     DWORD PTR [rbp-52], eax
.L10:
        mov     eax, DWORD PTR [rbp-72]
        cdqe
        imul    rax, rax, 8000000
        lea     r14, arr[rax]
        mov     eax, DWORD PTR [rbp-68]
        cdqe
        imul    rax, rax, 8000000
        add     rax, OFFSET FLAT:arr
        mov     rdi, rax
        mov     DWORD PTR [rbp-60], 0
        jmp     .L11
.L16:
        mov     eax, DWORD PTR [rbp-76]
        cdqe
        imul    rax, rax, 8000000
        lea     r15, arr[rax]
        mov     DWORD PTR [rbp-64], 0
        jmp     .L12
.L15:
        mov     r13d, 0
        mov     ebx, r12d
        jmp     .L13
.L14:
        movsx   rax, ebx
        sal     rax, 3
        add     rax, r14
        mov     rdx, QWORD PTR [rax]
        movsx   rax, ebx
        sal     rax, 3
        add     rax, r15
        mov     rax, QWORD PTR [rax]
        imul    rax, rdx
        add     r13, rax
.L13:
        sub     ebx, 1
        test    ebx, ebx
        jne     .L14
        movsx   rax, ebx
        sal     rax, 3
        add     rax, r14
        mov     rdx, QWORD PTR [rax]
        movsx   rax, ebx
        sal     rax, 3
        add     rax, r15
        mov     rax, QWORD PTR [rax]
        imul    rax, rdx
        add     r13, rax
        mov     eax, DWORD PTR [rbp-60]
        imul    eax, DWORD PTR [rbp-52]
        mov     edx, eax
        mov     eax, DWORD PTR [rbp-64]
        imul    eax, DWORD PTR [rbp-56]
        add     eax, edx
        cdqe
        sal     rax, 3
        add     rax, rdi
        mov     rdx, QWORD PTR [rax]
        mov     eax, DWORD PTR [rbp-60]
        imul    eax, DWORD PTR [rbp-52]
        mov     ecx, eax
        mov     eax, DWORD PTR [rbp-64]
        imul    eax, DWORD PTR [rbp-56]
        add     eax, ecx
        cdqe
        sal     rax, 3
        add     rax, rdi
        add     rdx, r13
        mov     QWORD PTR [rax], rdx
        movsx   rax, r12d
        sal     rax, 3
        add     r15, rax
        add     DWORD PTR [rbp-64], 1
.L12:
        mov     eax, r8d
        cmp     DWORD PTR [rbp-64], eax
        jl      .L15
        movsx   rax, r12d
        sal     rax, 3
        add     r14, rax
        add     DWORD PTR [rbp-60], 1
.L11:
        mov     eax, esi
        cmp     DWORD PTR [rbp-60], eax
        jl      .L16
        mov     eax, DWORD PTR [rbp-68]
.L8:
        add     rsp, 56
        pop     rbx
        pop     r12
        pop     r13
        pop     r14
        pop     r15
        pop     rbp
        ret