%include "io.inc"

section .bss
    inp resd 1

section .data
    suit db 'S', 'C', 'D', 'H'
    value db '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A', 

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, inp
    mov eax, dword[inp]
    dec eax
    
    cdq
    
    mov ecx, 13
    idiv ecx

    
    PRINT_CHAR [value + edx] 
    PRINT_CHAR [suit + eax]
    
    
    xor eax, eax
    ret