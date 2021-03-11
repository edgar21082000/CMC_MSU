%include "io.inc"

section .bss
    n resd 1
    m resd 1
    k resd 1
    d resd 1
    x resd 1
    y resd 1
    m1 resd 1
    m2 resd 1
    m3 resd 1
    m4 resd 1
    all_box resd 1
   
    
section .data
    koef dd 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, n
    GET_DEC 4, m
    GET_DEC 4, k
    GET_DEC 4, d
    GET_DEC 4, x
    GET_DEC 4, y
    
    
    mov eax, dword[x]
    shr eax, 1
    and eax, 1
    mov dword[m1], eax
    
    mov eax, dword[x]
    shr eax, 2
    and eax, 1
    mov dword[m2], eax
    
    mov eax, dword[x]
    shr eax, 3
    and eax, 1
    mov dword[m3], eax
    
    mov eax, dword[x]
    shr eax, 4
    and eax, 1
    mov dword[m4], eax
    
    mov eax, dword[m1]
    and eax, dword[m2]
    or eax, dword[m3]
    or eax, dword[m4]
    mov dword[koef], eax
    ; вычислил значение коэффицента ~ узнал какое время
    
    mov eax, dword[n]
    imul eax, dword[m]
    imul eax, dword[k]
    
    dec eax
    mov ecx, dword[d]
    cdq
    idiv ecx
    inc eax
    
    mov dword[all_box], eax
    
    dec eax
    mov ecx, 3
    cdq
    idiv ecx
    inc eax
    
    imul eax, dword[koef]
    sub dword[all_box], eax
    
    PRINT_DEC 4, all_box
    
    
    
    xor eax, eax
    ret