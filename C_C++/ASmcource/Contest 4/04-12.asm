%include "io.inc"

section .bss
    tmp resd 12
    key resd 40000
    l_ind resd 40000
    r_ind resd 40000
    i resd 1
    A resd 1; file *a

section .data
    root_ind dd 0
                        
section .rodata
    LCin_name db "input.bin", 0
    LCin_format db "rb", 0
    
    LCP db "%d ", 0
    
CEXTERN fopen
CEXTERN fclose
CEXTERN fread
CEXTERN printf

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp
    and esp, 0xFFFFFFF0
    sub esp, 32
    
    ;A = fopen("", "rb")
    mov dword[esp], LCin_name
    mov dword [esp+4], LCin_format
    call fopen
    mov dword[A], eax; теперь в [A] лежит file *
    
    mov dword[i], -1
   
.read:
    inc dword[i]
    mov ecx, [i]
    
    ;(=3)count = fread(tmp, sizeof(int), 3, A)
    mov eax, [A]
    mov dword[esp], tmp
    mov dword[esp+4], 4
    mov dword[esp+8], 3
    mov dword[esp+12], eax    
    
    call fread 
    cmp eax, 3
    jne .break
    
    ; copy tmp to arrays
    mov ecx, [i]
    mov eax, [tmp]
    mov [key + 4*ecx], eax
    mov eax, [tmp + 4]
    mov [l_ind + 4*ecx], eax
    mov eax, [tmp + 8]
    mov [r_ind + 4*ecx], eax
    ;-----------------------
    
    mov edx, [i]
    add [root_ind], edx
    
    cmp dword[l_ind + 4*edx], -1
    jne .redact_left
.2cmp:    
    cmp dword[r_ind + 4*edx], -1
    jne .redact_right
    
    jmp .read
    
.redact_left:
    mov eax, [l_ind + 4*edx]
    mov ecx, 12
    cdq
    idiv ecx
    
    mov edx, [i]
    mov [l_ind + 4*edx], eax
    sub [root_ind], eax
    jmp .2cmp
.redact_right:
    mov eax, [r_ind +4*edx]
    mov ecx, 12
    cdq
    idiv ecx
    
    mov edx, [i]
    mov [r_ind + 4*edx], eax
    sub [root_ind], eax
    jmp .read
        
.break:
    ;PRINT_DEC 4, key
    ;PRINT_DEC 4, [key+4]
    ;PRINT_DEC 4, [key+8]
    ;PRINT_DEC 4, l_ind
    ;PRINT_DEC 4, [l_ind+4]
    ;PRINT_DEC 4, [l_ind+8] 
    ;PRINT_DEC 4, r_ind
    ;PRINT_DEC 4, [r_ind+4]
    ;PRINT_DEC 4, [r_ind+8]
    ;PRINT_DEC 4, root_ind
    
    ;fclose(A)
    mov eax, dword[A]
    mov [esp], eax
    call fclose
    
    mov ecx, [root_ind]
    
    mov eax, [key + 4*ecx]
    mov [esp], eax
    mov eax, [l_ind +4*ecx]
    mov [esp+4], eax
    mov eax, [r_ind + 4*ecx]
    mov [esp+8], eax
    
    call print
    
    
    ;write your code here
    xor eax, eax
    leave
    ret
    
print:
    push ebp
    mov ebp, esp
    sub esp, 24; выровняли по 16 с выделением
    
    mov eax, [esp+32]; key
    mov dword[esp], LCP
    mov dword[esp+4], eax
    call printf
    
    mov eax, [esp+36]; l_ind
    cmp eax, -1
    jne .call_left
.2prn:
    mov eax, [esp+40]; r_ind
    cmp eax, -1
    jne .call_right
.rec_end:
    leave
    ret

.call_left:
    mov ecx, eax; ecx is index now
    
    mov eax, [key + 4*ecx]
    mov [esp], eax    
    mov eax, [l_ind + 4*ecx]
    mov [esp+4], eax 
    mov eax, [r_ind + 4*ecx]
    mov [esp+8], eax
    
    call print
    
    
    jmp .2prn
    
.call_right:
    mov ecx, eax; ecx is index now
    
    mov eax, [key + 4*ecx]
    mov [esp], eax    
    mov eax, [l_ind + 4*ecx]
    mov [esp+4], eax 
    mov eax, [r_ind + 4*ecx]
    mov [esp+8], eax
    
    call print
    
    jmp .rec_end