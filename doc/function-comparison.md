One of the challenges that pops up when you implement a C math library is deciding how to best structure your functions and data types.
Lets take 4x4 matrix multiplication as an example.
You have 3 options.

```
// representing the mat4 as a struct

typedef struct sMat4 {
    float x[4][4];
} sMat4;

Mat4 mult_A(const sMat4* a, const sMat4* b)
{
    Mat4 out;
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
        {
            out.x[i][j] = 0;
            for (int k = 0; k < 4; k++) 
                out.x[i][j] += a->x[i][k] * b->x[k][j];
        }
    return out;
}

Mat4 mult_B(const sMat4 a, const sMat4 b)
{
    Mat4 out;
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
        {
            out.x[i][j] = 0;
            for (int k = 0; k < 4; k++) 
                out.x[i][j] += a.x[i][k] * b.x[k][j];
        }
    return out;
}

// representing the mat4 as a length 4 array of length 4 arrays

typedef float aMat4[4][4];

void mult_C(const aMat4 a, const aMat4 b, aMat4 out)
{
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
        {
            out[i][j] = 0;
            for (int k = 0; k < 4; k++) 
                out[i][j] += a[i][k] * b[k][j];
        }
}

```

Putting aside developer friendlines, each of these 3 paths have different performance implications.

I tested all 3 on godbolt.org compiler explorer. Below are the results.

CC: x86-64 gcc 9.3
FLAGS: -O2 -Wall

```
mult_A:
        push    rbx
        mov     r11, rdi
        pxor    xmm2, xmm2
        lea     rdi, [rdx+64]
        lea     r9, [rdx+80]
        lea     r10, [rsp-64]
        mov     rbx, rsp
.L2:
        mov     rcx, rdi
        mov     r8, r10
.L4:
        lea     rax, [rcx-64]
        mov     rdx, rsi
        movaps  xmm1, xmm2
.L3:
        movss   xmm0, DWORD PTR [rdx]
        mulss   xmm0, DWORD PTR [rax]
        add     rax, 16
        add     rdx, 4
        addss   xmm1, xmm0
        cmp     rax, rcx
        jne     .L3
        lea     rcx, [rax+4]
        movss   DWORD PTR [r8], xmm1
        add     r8, 4
        cmp     rcx, r9
        jne     .L4
        add     r10, 16
        add     rsi, 16
        cmp     r10, rbx
        jne     .L2
        movdqa  xmm3, XMMWORD PTR [rsp-64]
        movdqa  xmm4, XMMWORD PTR [rsp-48]
        mov     rax, r11
        movdqa  xmm5, XMMWORD PTR [rsp-32]
        movdqa  xmm6, XMMWORD PTR [rsp-16]
        movups  XMMWORD PTR [r11], xmm3
        pop     rbx
        movups  XMMWORD PTR [r11+16], xmm4
        movups  XMMWORD PTR [r11+32], xmm5
        movups  XMMWORD PTR [r11+48], xmm6
        ret
mult_B:
        mov     r11, rdi
        lea     r8, [rsp+8]
        pxor    xmm2, xmm2
        lea     r10, [rsp-72]
        lea     rdi, [rsp+72]
        lea     r9, [rsp+152]
.L11:
        lea     rcx, [rsp+136]
        mov     rsi, r10
.L13:
        lea     rax, [rcx-64]
        mov     rdx, r8
        movaps  xmm1, xmm2
.L12:
        movss   xmm0, DWORD PTR [rdx]
        mulss   xmm0, DWORD PTR [rax]
        add     rax, 16
        add     rdx, 4
        addss   xmm1, xmm0
        cmp     rax, rcx
        jne     .L12
        lea     rcx, [rax+4]
        movss   DWORD PTR [rsi], xmm1
        add     rsi, 4
        cmp     rcx, r9
        jne     .L13
        add     r8, 16
        add     r10, 16
        cmp     r8, rdi
        jne     .L11
        movdqa  xmm3, XMMWORD PTR [rsp-72]
        movdqa  xmm4, XMMWORD PTR [rsp-56]
        mov     rax, r11
        movdqa  xmm5, XMMWORD PTR [rsp-40]
        movdqa  xmm6, XMMWORD PTR [rsp-24]
        movups  XMMWORD PTR [r11], xmm3
        movups  XMMWORD PTR [r11+16], xmm4
        movups  XMMWORD PTR [r11+32], xmm5
        movups  XMMWORD PTR [r11+48], xmm6
        ret
mult_C:
        push    rbx
        lea     r9, [rdi+16]
        lea     rbx, [rdi+64]
        pxor    xmm2, xmm2
        lea     r11, [rsi+16]
.L18:
        mov     r10, rsi
        mov     r8, rdx
.L20:
        mov     DWORD PTR [r8], 0x00000000
        mov     rcx, r10
        mov     rax, rdi
        movaps  xmm1, xmm2
.L19:
        movss   xmm0, DWORD PTR [rax]
        mulss   xmm0, DWORD PTR [rcx]
        add     rax, 4
        add     rcx, 16
        addss   xmm1, xmm0
        movss   DWORD PTR [r8], xmm1
        cmp     rax, r9
        jne     .L19
        add     r10, 4
        add     r8, 4
        cmp     r10, r11
        jne     .L20
        add     rdi, 16
        lea     r9, [rax+16]
        add     rdx, 16
        cmp     rdi, rbx
        jne     .L18
        pop     rbx
        ret
        ```


CC: x86-64 gcc 9.3
FLAGS: -O3 -Wall

```
mult_A:
        movss   xmm0, DWORD PTR [rdx+12]
        movss   xmm5, DWORD PTR [rdx+8]
        pxor    xmm11, xmm11
        mov     rax, rdi
        movss   xmm10, DWORD PTR [rdx+20]
        movss   xmm3, DWORD PTR [rdx+16]
        unpcklps        xmm5, xmm0
        movss   xmm7, DWORD PTR [rdx+24]
        movss   xmm0, DWORD PTR [rdx+28]
        movss   xmm1, DWORD PTR [rdx+4]
        movss   xmm6, DWORD PTR [rdx]
        unpcklps        xmm3, xmm10
        unpcklps        xmm7, xmm0
        movaps  xmm10, xmm3
        movss   xmm2, DWORD PTR [rdx+44]
        movss   xmm0, DWORD PTR [rdx+52]
        movlhps xmm10, xmm7
        unpcklps        xmm6, xmm1
        movss   xmm4, DWORD PTR [rdx+40]
        movss   xmm7, DWORD PTR [rdx+48]
        movss   xmm1, DWORD PTR [rdx+60]
        movaps  xmm12, xmm6
        movss   xmm6, DWORD PTR [rdx+56]
        unpcklps        xmm4, xmm2
        unpcklps        xmm7, xmm0
        movups  xmm2, XMMWORD PTR [rsi+16]
        movlhps xmm12, xmm5
        unpcklps        xmm6, xmm1
        movaps  xmm8, xmm7
        movups  xmm0, XMMWORD PTR [rsi]
        movss   xmm9, DWORD PTR [rdx+36]
        movlhps xmm8, xmm6
        movaps  xmm6, xmm2
        movaps  xmm3, xmm2
        movss   xmm5, DWORD PTR [rdx+32]
        shufps  xmm6, xmm2, 0
        mulps   xmm6, xmm12
        shufps  xmm3, xmm2, 85
        movaps  xmm7, xmm0
        mulps   xmm3, xmm10
        unpcklps        xmm5, xmm9
        shufps  xmm7, xmm0, 0
        mulps   xmm7, xmm12
        movaps  xmm9, xmm5
        movlhps xmm9, xmm4
        movaps  xmm4, xmm0
        shufps  xmm4, xmm0, 85
        mulps   xmm4, xmm10
        addps   xmm6, xmm11
        addps   xmm7, xmm11
        addps   xmm6, xmm3
        movaps  xmm3, xmm2
        shufps  xmm3, xmm2, 170
        mulps   xmm3, xmm9
        addps   xmm7, xmm4
        movaps  xmm4, xmm0
        shufps  xmm4, xmm0, 170
        mulps   xmm4, xmm9
        addps   xmm6, xmm3
        movaps  xmm3, xmm2
        shufps  xmm3, xmm2, 255
        movups  xmm2, XMMWORD PTR [rsi+32]
        mulps   xmm3, xmm8
        addps   xmm7, xmm4
        movaps  xmm4, xmm0
        movaps  xmm5, xmm2
        shufps  xmm4, xmm0, 255
        movaps  xmm0, xmm2
        shufps  xmm5, xmm2, 0
        mulps   xmm5, xmm12
        shufps  xmm0, xmm2, 85
        mulps   xmm0, xmm10
        mulps   xmm4, xmm8
        addps   xmm3, xmm6
        addps   xmm5, xmm11
        movups  XMMWORD PTR [rdi+16], xmm3
        addps   xmm4, xmm7
        addps   xmm5, xmm0
        movaps  xmm0, xmm2
        shufps  xmm0, xmm2, 170
        mulps   xmm0, xmm9
        shufps  xmm2, xmm2, 255
        mulps   xmm2, xmm8
        movups  XMMWORD PTR [rdi], xmm4
        addps   xmm5, xmm0
        movups  xmm0, XMMWORD PTR [rsi+48]
        movaps  xmm1, xmm0
        shufps  xmm1, xmm0, 0
        mulps   xmm1, xmm12
        addps   xmm2, xmm5
        movups  XMMWORD PTR [rdi+32], xmm2
        addps   xmm1, xmm11
        movaps  xmm11, xmm0
        shufps  xmm11, xmm0, 85
        mulps   xmm10, xmm11
        addps   xmm1, xmm10
        movaps  xmm10, xmm0
        shufps  xmm10, xmm0, 170
        mulps   xmm9, xmm10
        shufps  xmm0, xmm0, 255
        mulps   xmm0, xmm8
        addps   xmm1, xmm9
        addps   xmm0, xmm1
        movups  XMMWORD PTR [rdi+48], xmm0
        ret
mult_B:
        movss   xmm0, DWORD PTR [rsp+84]
        movss   xmm5, DWORD PTR [rsp+80]
        mov     rax, rdi
        pxor    xmm11, xmm11
        movss   xmm10, DWORD PTR [rsp+92]
        movss   xmm3, DWORD PTR [rsp+88]
        unpcklps        xmm5, xmm0
        movss   xmm7, DWORD PTR [rsp+96]
        movss   xmm0, DWORD PTR [rsp+100]
        movss   xmm1, DWORD PTR [rsp+76]
        movss   xmm6, DWORD PTR [rsp+72]
        unpcklps        xmm3, xmm10
        unpcklps        xmm7, xmm0
        movaps  xmm10, xmm3
        movss   xmm2, DWORD PTR [rsp+116]
        movss   xmm0, DWORD PTR [rsp+124]
        movlhps xmm10, xmm7
        unpcklps        xmm6, xmm1
        movss   xmm4, DWORD PTR [rsp+112]
        movss   xmm7, DWORD PTR [rsp+120]
        movss   xmm1, DWORD PTR [rsp+132]
        movaps  xmm12, xmm6
        movss   xmm6, DWORD PTR [rsp+128]
        unpcklps        xmm4, xmm2
        unpcklps        xmm7, xmm0
        movups  xmm2, XMMWORD PTR [rsp+24]
        movlhps xmm12, xmm5
        unpcklps        xmm6, xmm1
        movaps  xmm8, xmm7
        movups  xmm0, XMMWORD PTR [rsp+8]
        movss   xmm9, DWORD PTR [rsp+108]
        movlhps xmm8, xmm6
        movaps  xmm6, xmm2
        movaps  xmm3, xmm2
        movss   xmm5, DWORD PTR [rsp+104]
        shufps  xmm6, xmm2, 0
        mulps   xmm6, xmm12
        shufps  xmm3, xmm2, 85
        movaps  xmm7, xmm0
        mulps   xmm3, xmm10
        unpcklps        xmm5, xmm9
        shufps  xmm7, xmm0, 0
        mulps   xmm7, xmm12
        movaps  xmm9, xmm5
        movlhps xmm9, xmm4
        movaps  xmm4, xmm0
        shufps  xmm4, xmm0, 85
        mulps   xmm4, xmm10
        addps   xmm6, xmm11
        addps   xmm7, xmm11
        addps   xmm6, xmm3
        movaps  xmm3, xmm2
        shufps  xmm3, xmm2, 170
        mulps   xmm3, xmm9
        addps   xmm7, xmm4
        movaps  xmm4, xmm0
        shufps  xmm4, xmm0, 170
        mulps   xmm4, xmm9
        addps   xmm6, xmm3
        movaps  xmm3, xmm2
        shufps  xmm3, xmm2, 255
        movups  xmm2, XMMWORD PTR [rsp+40]
        mulps   xmm3, xmm8
        addps   xmm7, xmm4
        movaps  xmm4, xmm0
        movaps  xmm5, xmm2
        shufps  xmm4, xmm0, 255
        movaps  xmm0, xmm2
        shufps  xmm5, xmm2, 0
        mulps   xmm5, xmm12
        shufps  xmm0, xmm2, 85
        mulps   xmm0, xmm10
        mulps   xmm4, xmm8
        addps   xmm3, xmm6
        addps   xmm5, xmm11
        movups  XMMWORD PTR [rdi+16], xmm3
        addps   xmm4, xmm7
        addps   xmm5, xmm0
        movaps  xmm0, xmm2
        shufps  xmm0, xmm2, 170
        mulps   xmm0, xmm9
        shufps  xmm2, xmm2, 255
        mulps   xmm2, xmm8
        movups  XMMWORD PTR [rdi], xmm4
        addps   xmm5, xmm0
        movups  xmm0, XMMWORD PTR [rsp+56]
        movaps  xmm1, xmm0
        shufps  xmm1, xmm0, 0
        mulps   xmm1, xmm12
        addps   xmm2, xmm5
        movups  XMMWORD PTR [rdi+32], xmm2
        addps   xmm1, xmm11
        movaps  xmm11, xmm0
        shufps  xmm11, xmm0, 85
        mulps   xmm10, xmm11
        addps   xmm1, xmm10
        movaps  xmm10, xmm0
        shufps  xmm10, xmm0, 170
        mulps   xmm9, xmm10
        shufps  xmm0, xmm0, 255
        mulps   xmm0, xmm8
        addps   xmm1, xmm9
        addps   xmm0, xmm1
        movups  XMMWORD PTR [rdi+48], xmm0
        ret
mult_C:
        lea     rax, [rdx+64]
        pxor    xmm2, xmm2
.L5:
        mov     DWORD PTR [rdx], 0x00000000
        movss   xmm1, DWORD PTR [rdi]
        add     rdx, 16
        add     rdi, 16
        mulss   xmm1, DWORD PTR [rsi]
        addss   xmm1, xmm2
        movss   DWORD PTR [rdx-16], xmm1
        movss   xmm0, DWORD PTR [rdi-12]
        mulss   xmm0, DWORD PTR [rsi+16]
        addss   xmm1, xmm0
        movss   DWORD PTR [rdx-16], xmm1
        movss   xmm0, DWORD PTR [rdi-8]
        mulss   xmm0, DWORD PTR [rsi+32]
        addss   xmm0, xmm1
        movss   DWORD PTR [rdx-16], xmm0
        movss   xmm1, DWORD PTR [rdi-4]
        mulss   xmm1, DWORD PTR [rsi+48]
        mov     DWORD PTR [rdx-12], 0x00000000
        addss   xmm0, xmm1
        movss   DWORD PTR [rdx-16], xmm0
        movss   xmm1, DWORD PTR [rdi-16]
        mulss   xmm1, DWORD PTR [rsi+4]
        addss   xmm1, xmm2
        movss   DWORD PTR [rdx-12], xmm1
        movss   xmm0, DWORD PTR [rdi-12]
        mulss   xmm0, DWORD PTR [rsi+20]
        addss   xmm1, xmm0
        movss   DWORD PTR [rdx-12], xmm1
        movss   xmm0, DWORD PTR [rdi-8]
        mulss   xmm0, DWORD PTR [rsi+36]
        addss   xmm0, xmm1
        movss   DWORD PTR [rdx-12], xmm0
        movss   xmm1, DWORD PTR [rdi-4]
        mulss   xmm1, DWORD PTR [rsi+52]
        mov     DWORD PTR [rdx-8], 0x00000000
        addss   xmm0, xmm1
        movss   DWORD PTR [rdx-12], xmm0
        movss   xmm1, DWORD PTR [rdi-16]
        mulss   xmm1, DWORD PTR [rsi+8]
        addss   xmm1, xmm2
        movss   DWORD PTR [rdx-8], xmm1
        movss   xmm0, DWORD PTR [rdi-12]
        mulss   xmm0, DWORD PTR [rsi+24]
        addss   xmm1, xmm0
        movss   DWORD PTR [rdx-8], xmm1
        movss   xmm0, DWORD PTR [rdi-8]
        mulss   xmm0, DWORD PTR [rsi+40]
        addss   xmm0, xmm1
        movss   DWORD PTR [rdx-8], xmm0
        movss   xmm1, DWORD PTR [rdi-4]
        mulss   xmm1, DWORD PTR [rsi+56]
        mov     DWORD PTR [rdx-4], 0x00000000
        addss   xmm0, xmm1
        movss   DWORD PTR [rdx-8], xmm0
        movss   xmm1, DWORD PTR [rdi-16]
        mulss   xmm1, DWORD PTR [rsi+12]
        addss   xmm1, xmm2
        movss   DWORD PTR [rdx-4], xmm1
        movss   xmm0, DWORD PTR [rdi-12]
        mulss   xmm0, DWORD PTR [rsi+28]
        addss   xmm1, xmm0
        movss   DWORD PTR [rdx-4], xmm1
        movss   xmm0, DWORD PTR [rdi-8]
        mulss   xmm0, DWORD PTR [rsi+44]
        addss   xmm0, xmm1
        movss   DWORD PTR [rdx-4], xmm0
        movss   xmm1, DWORD PTR [rdi-4]
        mulss   xmm1, DWORD PTR [rsi+60]
        addss   xmm0, xmm1
        movss   DWORD PTR [rdx-4], xmm0
        cmp     rax, rdx
        jne     .L5
        ret
        ```
O2 Result:
mult_A: 42 instructions
mult_B: 40 instructions
mult_C: 30 instructions

O3 Results:
mult_A: 105 instructions
mult_B: 105 instructions
mult_C: 76 instructions

So in both O2 and O3 cases, mult_C performs better, emitting about 72% of the instructions of the other two methods.
