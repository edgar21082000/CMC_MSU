%include "io.inc"
    
section .bss
    num resd 1
    n resd 1
    i resd 1
section .data
    new_num dd 0
    rev_num dd 0   
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_UDEC 4, num
    GET_UDEC 4, n
    mov ecx, 0
    mov [i], ecx
    
    mov edx, [num]
    add [new_num], edx; copy num
    
    cmp dword[n], 0
    jz .check
    
.new_num:
    mov dword[rev_num], 0 
    push dword[new_num]
    push dword[rev_num]
    call revers
    add [new_num], eax
    
 
    add esp, 8
    
    mov ecx, [i]
    inc ecx
    mov [i], ecx
    cmp ecx, [n]
    jne .new_num 
    
    
    
.check:
    mov dword[rev_num], 0
    push dword[new_num]
    push dword[rev_num]; push 0
    call revers
    add esp, 8
   
    cmp eax, [new_num]
    je .yes
    jne .no
.yes:
    PRINT_STRING 'Yes'
    NEWLINE
    PRINT_UDEC 4, eax     
    jmp .end
.no:
    PRINT_STRING 'No'
    jmp .end
.end:                                                                        
    xor eax, eax
    ret

   

revers:
    push ebp
    mov ebp, esp
    mov eax, [esp+12]
    mov ecx, [esp+8]
    sub esp, 8
    
    mov [esp], ecx; [esp] consist rev_num
    
    mov ecx, 10
    xor edx, edx
    div ecx
    mov [esp+4], eax
    imul ecx, [esp]
    mov [esp], ecx
    add [esp], edx
    
    test eax, eax
    jz .rec_end
    call revers
.rec_end:
    mov eax, [esp]
    mov [esp+16], eax
    leave
    ret     