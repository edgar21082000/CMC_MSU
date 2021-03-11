%include "io.inc"

section .bss
    m resd 1
    d resd 1
    ans resd 1

section .text
global CMAIN
CMAIN:
    GET_DEC 4, m
    GET_DEC 4, d
    
    mov eax, dword[m]
    mov ecx, 2
    cdq
    idiv ecx; теперь в eax лежит частное m/2
    
    mov dword[ans], 0
    sub dword[ans], eax
    
    dec dword[m]
    imul eax, dword[m], 42
    
    add dword[ans], eax
    
    mov eax, dword[d]
    add dword[ans], eax
    
    PRINT_DEC 4, ans
    
    xor eax, eax
    ret