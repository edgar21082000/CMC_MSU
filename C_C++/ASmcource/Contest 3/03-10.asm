%include "io.inc"
section .bss
    sum_a resd 1
    sum_b resd 1
    n resd 1
    gcdiv resd 1
    i resd 1
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, n
    GET_DEC 4, sum_a
    GET_DEC 4, sum_b
    
    mov ecx, 1
    mov [i], ecx
    cmp ecx, [n]
    je .reduction
    
.for:
    GET_DEC 4, eax
    GET_DEC 4, ebx
    mov edx, ebx
    imul eax, [sum_b]
    imul ebx, [sum_a]
    mov [sum_a], ebx
    add [sum_a], eax
    imul edx, [sum_b]
    mov [sum_b], edx
    
   
    
    push dword[sum_b]
    push dword[sum_a]
    call gcd
    add esp, 8
    
    mov [gcdiv], eax; now edx is gcd
    
    
    ;сокращаем
    mov eax, [sum_a]
    cdq
    idiv dword[gcdiv]
    mov [sum_a], eax
    
    mov eax, [sum_b]
    cdq
    idiv dword[gcdiv]
    mov [sum_b], eax
    ;сокращаем
    
    
    mov ecx, [i]
    inc ecx
    mov [i], ecx
    cmp ecx, [n]
    jne .for
    jmp .print
    


.reduction:
    push dword[sum_b]
    push dword[sum_a]
    call gcd
    add esp, 8
    
    mov [gcdiv], eax; now edx is gcd
    
    
    ;сокращаем
    mov eax, [sum_a]
    cdq
    idiv dword[gcdiv]
    mov [sum_a], eax
    
    mov eax, [sum_b]
    cdq
    idiv dword[gcdiv]
    mov [sum_b], eax

.print:
    PRINT_DEC 4, sum_a
    PRINT_CHAR ' '
    PRINT_DEC 4, sum_b    
    ;write your code here
    xor eax, eax
    ret
    
gcd:
    push ebp
    mov ebp, esp
    sub esp, 8
    
    ; eax is tmp
    mov eax, [esp+16]; it's sum_a
    mov [esp], eax
    mov eax, [esp+20]; it's sum_b
    mov [esp+4], eax

    
.while:
    mov ecx, [esp+4]
    test ecx, ecx
    jz .return_a

    mov eax, [esp]
    cdq
    idiv ecx
    mov [esp], ecx
    mov [esp+4], edx
    jmp .while

.return_a:
    mov eax, [esp]
    leave 
    ret