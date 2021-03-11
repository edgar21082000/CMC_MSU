%include "io.inc"

section .bss
    a resd 1
    b resd 1
    c resd 1
    d resd 1

section .text
global CMAIN
CMAIN:
    GET_HEX 4, a
    GET_HEX 4, b
    GET_HEX 4, c
    
    mov eax, dword[c]
    and dword[a], eax; оставляем биты а - где у с 1
    
    not eax
    and dword[b], eax; оставляем биты b где у not c 1
    
    mov eax, dword[a]
    add eax, dword[b]
    mov dword[d], eax
    PRINT_HEX 4, d


    xor eax, eax
    ret