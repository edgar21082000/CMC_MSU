%include "io.inc"

section .data 
    count dd 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    push dword[count]
    call mp
    add esp, 4
    
    xor eax, eax
    ret

mp:
    push ebp
    mov ebp, esp
    mov ecx, [esp+8]; ecx = count
    sub esp, 8
    GET_DEC 4, [esp+4]; read num
    cmp dword[esp+4], 0
    je .end
    
    mov [esp], ecx;
    add dword[esp], 1; current count
    mov eax, [esp]; copy count
    and eax, 1
    jne .if1; if count%2 == 1   
    jmp .else; if count%2 == 0
.if1:
    PRINT_DEC 4, [esp+4]  
    PRINT_CHAR ' '  
    call mp
    leave
    ret
.else:
    call mp
    PRINT_DEC 4, [esp+4]
    PRINT_CHAR ' '
    leave
    ret
.end:
    leave
    ret
 
    
 