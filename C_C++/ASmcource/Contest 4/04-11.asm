%include "io.inc"

section .bss
    list resd 12024; 1-n 0 and n+1 is free
    begin resd 1
    n resd 1
    m resd 1
    key1 resd 1
    key2 resd 2
    i resd 1
    j resd 1

section .rodata
    LCS db "%d %d", 0
    LCP db "%d ", 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp
    and esp, 0xFFFFFFF0
    sub esp, 16
    
    mov dword[esp], LCS
    mov dword[esp+4], n
    mov dword[esp+8], m
    call scanf
    
    
    
    
    mov dword[i], -1
.link:
    inc dword[i]
    mov ecx, [i]
    cmp ecx, [n]
    jg .break_link
    
    mov [list + 4*ecx +12], ecx
    inc dword[list + 4*ecx +12];
    
    dec ecx
    lea eax, [list + 4*ecx +12]; *left
    inc ecx
    mov [list + 4*ecx + 4 +12], eax
    
    inc ecx
    lea eax, [list + 4*ecx +12]; *right
    dec ecx
    mov [list + 4*ecx + 20], eax ; +8 +12
     
    jmp .link   
.break_link:
    
    ; зануляем края
    mov ecx, 1
    mov dword[list + 4*ecx + 16], 0 ; +4 +12
    mov ecx, [n]
    mov dword[list + 4*ecx + 20], 0 ; +8 +12
    ; -------------    
    
    lea eax, [list + 16]; +4 +12
    mov [begin], eax; запомнили начало списка
    
    mov dword[j], 0
    mov dword[esp], LCS
.for:
    inc dword[j]
    mov ecx, [j]
    cmp ecx, [m]
    jg .break_for
    
    mov dword[esp+4], key1
    mov dword[esp+4], key2
    call scanf
    
    mov esi, [key1]; eax - index of struct with value = key1
    mov edi, [key2]; edx - index of struct with valuy = key2
    
    mov eax, dword[list + 4*esi + 16] ; +4 +12
    test eax, eax
    jz .for
    
    mov eax, dword[list + 4*edi + 20] ; &list key2 right
    mov edx, dword[list + 4*esi + 16] ; &list key1 left
    mov edx, dword[edx] ; list key1 left
    mov dword[edx + 8], eax ; list key1 left right = &list key2 right
    
    mov eax, dword[eax] ; list key2 right
    mov edx, dword[list + 4*esi + 16] ; &list key1 left
    mov dword[eax + 4], edx ; list key2 right left = &list key1 left
    
    mov dword[list + 4*eax + 16], 0; list[key1].left = NULL
    
    mov eax, [begin] ; &begin
    mov dword[list + 4*edi + 20], eax
    
    mov eax, dword[begin]
    mov eax, dword[eax]
    mov edx, dword[list + 4*esi +12]
    mov dword[eax + 4], edx
    
    lea eax, [list + 4*esi +12]
    mov [begin], eax; запомнили начало списка
     
    
    
    
              
    
    jmp .for
.break_for:


    
    ;write your code here
    xor eax, eax
    ret