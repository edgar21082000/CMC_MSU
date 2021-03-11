%include "io.inc"

section .bss
    k resd 1
    i resd 1
    cur_num resd 1
section .data

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, [k]
    
    mov ecx, 0
    mov [i], ecx
    mov dword[cur_num], 0
.search:
    add dword[cur_num], 1
    push dword[cur_num]
    call insuff
    add esp, 4
    
    mov ecx, [i]
    cmp eax, [cur_num]
    jl .ecx_plus
    jmp .search

.ecx_plus:
    inc ecx;
    mov [i], ecx

    cmp ecx, [k]
    jne .search
    
    
    PRINT_DEC 4, cur_num
    xor eax, eax
    ret
    
    
insuff:
    push ebp
    mov ebp, esp
    mov eax, [esp+8]
    sub esp, 8
    
    mov dword[esp], 0; sum of divider
    mov [esp+4], eax; copy eax
    mov ecx, 1
    cmp ecx, eax
    je .return
    
.for:
    cdq
    idiv ecx
    test edx, edx
    jz .add_sum
    mov eax, [esp+4]
    inc ecx
    
    cmp ecx, eax
    je .return
    jne .for  
    
.add_sum:
    add [esp], ecx
    mov eax, [esp+4]
    inc ecx
    cmp ecx, eax
    je .return
    jmp .for    
    
.return:
    mov eax, [esp]
    leave
    ret
    