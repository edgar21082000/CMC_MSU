%include "io.inc"

section .bss
    k_sum resw 32
    k resd 1
    num resd 1
section .data
    s dw 0
    dvd dd 2

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_UDEC 4, num
    GET_UDEC 4, k
    
.search:
    push dword[k]
    push dword[num]
    call dec_to_k
    add esp, 8
    
    xor ecx, ecx
    mov cx, [k_sum + 2*eax]
    xor edx, edx
    div dword[dvd]
    sub cx, [k_sum + 2*eax]; sum[i] - 2*sum[i/2] ==? 0
    sub cx, [k_sum + 2*eax]
    test ecx, ecx
    jz .break
    
    mov ecx, 1
.null:
    mov word[k_sum + 2*ecx], 0
    inc ecx
    cmp ecx, 32
    jl .null
    mov word[s], 0
    
    inc dword[num]
    jmp .search

.break:
    PRINT_UDEC 4, num            
    ;write your code here
    xor eax, eax
    ret
    
dec_to_k:
    push ebp
    mov ebp, esp
    sub esp, 8
    
    ;eax ~ tmp
    mov eax, [esp+16]; num
    mov [esp], eax
    mov eax, [esp+20]; k
    mov [esp+4], eax;
    
    mov eax, [num]; будем делить => перводить в другую систему счисления
    mov ecx, 0
    
    test eax, eax
    jz .return
.for:
    xor edx, edx
    div dword[k]
    add [s], dx
    mov dx, [s]
    mov [k_sum + 2*ecx], dx
    
    test eax, eax
    jz .return
    
    inc ecx
    jmp .for
.return:
    mov eax, ecx
    leave 
    ret       
    