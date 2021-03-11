%include "io.inc"

section .bss
    tmp resd 1
    k resd 1

section .data
    max dd 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_UDEC 4, eax; write N
    GET_UDEC 4, k; write K
    
    mov ecx, dword[k]
    dec ecx
    
    mov edx, 0x80000000
    
    jecxz .1end
.1: ; create mask
    sar edx, 1
    loop .1
.1end:    
    mov ecx, 33;  counter
    sub ecx, dword[k] 

    
    mov ebx, 0
    inc ecx; костыль лля счетчика, типо загружаем 0
.2_0: ; if (tmp>max) max = tmp
    mov dword[max], ebx
    sub ecx, 1; если ecx стал 0 то печатаем
    je .out

.2: ;(for ecx, ecx!=0, ecx--)   
    mov dword[tmp], eax
    and dword[tmp], edx
    
    dec ecx ; сдвигаем на ecx-1
    shr dword[tmp], cl; получил текущее временное число из к бит; cl состоит в ecx - так что все нормально
    inc ecx; возращаем настоящее значение счетчика
    
    shr edx, 1; сдвинули маску на 1
    
    mov ebx, dword[tmp]
    cmp ebx, dword[max]; сравниваем с текущим максимумом
    jge .2_0
    
    sub ecx, 1
    jne .2 ; пока ecx не 0 крутимся в цикле
    
                    
             
.out:
    PRINT_UDEC 4, max
     
    xor eax, eax
    ret