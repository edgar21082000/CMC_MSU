%include "io.inc"


section .bss
    ui resb 1
    start resb 2
    finish resb 2  
    diff resb 2

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_STRING start, 3; maxsz - 1 !!!
    GET_CHAR ui; считал пробел
    GET_STRING finish, 4;
    
    mov al, byte[start] 
    sub al, byte[finish]
    
    cbw
    xor al, ah; берем модуль числа в al
    sub al, ah
    
    mov byte[diff], al
    
    ;----------------------
    
    mov al, byte[start + 1] 
    sub al, byte[finish + 1]
    
    cbw
    xor al, ah; берем модуль числа в al
    sub al, ah
    
    add byte[diff], al
    PRINT_DEC 1, diff
     
    xor eax, eax
    ret