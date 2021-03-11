%include "io.inc"

section .bss
    a resd 1
    b resd 1
    c resd 1
    V resd 1
    min resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, a
    GET_DEC 4, b
    GET_DEC 4, c
    GET_DEC 4, V
    
    mov eax, dword[a]
    mul dword[b]
    mul dword[c]
    
   
    div dword[V]
    
    mov dword[min], eax
    
    PRINT_DEC 4, min
    
    xor eax, eax
    ret