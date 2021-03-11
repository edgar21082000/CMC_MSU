%include "io.inc"

section .bss
    a11 resd 1
    a12 resd 1
    a21 resd 1
    a22 resd 1
    b1 resd 1
    b2 resd 1
    x resd 1
    y resd 1
    
section .text
global CMAIN
CMAIN:
    GET_UDEC 4, [a11]
    GET_UDEC 4, [a12]
    GET_UDEC 4, [a21]
    GET_UDEC 4, [a22]
    GET_UDEC 4, [b1]
    GET_UDEC 4, [b2]
    
    xor edx, edx
    mov edx, dword[a22]
    and edx, dword[b1]
    mov ebx, dword[a12]
    and ebx, dword[b2]
    xor edx, ebx
    
    xor ecx, ecx
    mov ecx, dword[a21]
    and ecx, dword[b1]
    mov ebx, dword[a11]
    and ebx, dword[b2]
    xor ecx, ebx
    
    xor eax, eax
    mov eax, dword[a11]
    and eax, dword[a22]
    mov ebx, dword[a12]
    and ebx, dword[a21]
    xor eax, ebx
    
    and edx, eax
    and ecx, eax
    
    mov dword[x], edx
    mov dword[y], ecx
    
    ; y = ac | ~a11(a12b1) | ~a21(a22b2)
    
    mov ecx, dword[a11]
    not ecx
    and ecx, dword[a12]
    and ecx, dword[b1]
    
    or dword[y], ecx
    
    mov ecx, dword[a21]
    not ecx
    and ecx, dword[a22]
    and ecx, dword[b2]
    
    or dword[y], ecx
    
    ; x = ad | (b1^a12y)a11 | (b2^a22y)a21
    
    mov edx, dword[y]
    and edx, dword[a12]
    xor edx, dword[b1]
    and edx, dword[a11]
    
    or dword[x], edx
    
    mov edx, dword[y]
    and edx, dword[a22]
    xor edx, dword[b2]
    and edx, dword[a21]
    
    or dword[x], edx
    
    PRINT_UDEC 4, [x]
    PRINT_CHAR ' '
    PRINT_UDEC 4, [y]
    
    xor eax, eax
    ret