%include "io.inc"

section .bss
    n resd 1
    i resd 1
    j resd 1
    ans resd 1
    arr resb 5500


section .rodata
    LCSint db "%d", 0
    LCSstr db "%s", 0
    LCP db "%d", 10, 0 
        
CEXTERN strcmp
CEXTERN scanf
CEXTERN printf

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp
    and esp, 0xFFFFFFF0
    sub esp, 16
    
    mov dword[esp], LCSint
    mov dword[esp+4], n
    call scanf
    
    mov eax, [n]
    mov [ans], eax
    
    
    mov ecx, 0
    mov [i], ecx
.read:
    cmp ecx, [n]
    je .break
    
    mov edx, 11
    imul edx, ecx
    
    mov dword[esp], LCSstr
    lea eax, [arr + edx]
    mov dword[esp+4], eax
    call scanf
    
    inc dword[i]
    mov ecx, [i]
    jmp .read
.break:
    mov dword[i], -1
    
.for1:    
    inc dword[i]
    mov ecx, [i]
    inc ecx
    mov [j], ecx
    
    cmp ecx, [n]
    jg .out
    
    
    mov edx, 11
    imul edx, dword[i]
    lea eax, [arr + edx]
    mov dword[esp], eax
.for2:
    mov edx, 11
    imul edx, dword[j]
    lea eax, [arr + edx]
    mov dword[esp+4], eax
    
    call strcmp
    test eax, eax
    jz .minus
    
    inc dword[j]
    mov ecx, [j]
    cmp ecx, [n]
    jle .for2
    jg .for1
 
.minus:
    dec dword[ans]
    jmp .for1
    
.out:
    mov dword[esp], LCP
    mov eax, [ans]
    mov [esp+4], eax
    call printf
    
    xor eax, eax
    leave 
    ret
