%include "io.inc"

section .bss 
    N resd 1
    arr resd 500000
    min_arr resd 250000; укзатель на массив
    max_arr resd 250000

section .data
    loc_min dd 0
    loc_max dd 0    
   
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, N
    cmp dword[N], 2
    jle .out
    
    mov ecx, 0
.get_num:
    GET_DEC 4, [arr + 4*ecx]
    inc ecx
    cmp ecx, dword[N]
    jne .get_num
    
    mov ecx, 0
    dec dword[N]
    




.for:
    inc ecx
    cmp ecx, dword[N]
    je .out; если дошли до последнего то выходим из цикла 
    
    mov eax, [arr + 4*ecx - 4]
    cmp eax, dword[arr + 4*ecx]
    je .for; ни то ни другое
    
    jl .possible_max; if [n-1] < n
    jg .possible_min; if [n-1] > n
    
.possible_min:
    mov eax, [arr + 4*ecx + 4]
    cmp eax, dword[arr + 4*ecx]
    jle .for; не loc
    ; иначе все норми это loc
    mov edx, [loc_min]
    mov [min_arr + 4*edx], ecx
    inc dword[loc_min]
    jmp .for
 
.possible_max:
    mov eax, [arr + 4*ecx + 4]
    cmp eax, dword[arr + 4*ecx]
    jge .for; не loc
    ; иначе все норм
    mov edx, [loc_max]
    mov [max_arr + 4*edx], ecx
    inc dword[loc_max]
    jmp .for       
    
    
; печать ответа
.out:
    mov ecx, 0
    PRINT_DEC 4, loc_min
    NEWLINE
    cmp dword[loc_min], ecx
    je .no_min
.print_min:
    PRINT_DEC 4, min_arr + 4*ecx
    PRINT_CHAR ' '
    inc ecx
    cmp dword[loc_min], ecx
    jne .print_min
    NEWLINE
.no_min:
    mov ecx, 0
    PRINT_DEC 4, loc_max
    NEWLINE
    cmp dword[loc_max], ecx
    je .no_max
.print_max:
    PRINT_DEC 4, max_arr + 4*ecx
    PRINT_CHAR ' '
    inc ecx
    cmp dword[loc_max], ecx
    jne .print_max
    NEWLINE
.no_max:    
    
    xor eax, eax
    ret