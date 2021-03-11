%include "io.inc"

section .bss
    x resd 1
    
section .rodata
    LCS db "%u", 0; scanf
    LCP db "0x%08X", 10, 0; printf 

CEXTERN scanf
CEXTERN printf

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    and esp, 0xFFFFFFF0
    sub esp, 16
    
.while:
    mov dword[esp+4], x
    mov dword[esp], LCS
    call scanf
    
    
    cmp eax, 1
    jne .end
    
    mov edx, dword[x]
    mov dword[esp+4], edx
    mov dword[esp], LCP
    call printf
    
    
    jmp .while
    
.end:  
    leave
    xor eax, eax
    ret