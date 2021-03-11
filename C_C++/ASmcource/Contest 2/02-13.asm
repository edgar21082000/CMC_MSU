%include "io.inc"

section .bss
    N resd 1
    k resd 1
    right resd 1
    mask resd 1
    arr resd 1000000

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, N
    mov ecx, 0
    
    cmp ecx, dword[N]
    je .return_0
.read_arr:
    GET_UDEC 4, [arr + 4*ecx]
    inc ecx
    cmp ecx, dword[N]
    jne .read_arr
    
    dec ecx
    mov eax, [arr + 4*ecx]
    mov [right], eax ; запомнили правое число
;---------------------------------------------   

    mov ecx, 0
    GET_UDEC 4, k; считали к и теперь строим маску
    cmp ecx, dword[k]
    je .out; если к = 0 то последовательность не меняется
   
    mov ecx, 0
    mov edx, 1

.for_mask:
    add [mask], edx
    shl edx, 1
    inc ecx
    cmp ecx, dword[k]
    jne .for_mask
;---------------------------------------------   
   

    mov edi, [N]
    dec edi
    cmp edi, 0; усли одна цифра то в конец
    je .out_ror

   
     
.for:
    mov ecx, [k]
    shr dword[arr + 4*edi], cl
    
    mov ebx, [arr + 4*edi - 4]
    and ebx, [mask]
    
    mov ecx, 32
    sub ecx, [k]
    shl ebx, cl
    
    or dword[arr + 4*edi], ebx
    
    dec edi
    cmp edi, 0
    jne .for
;сделали для всех кроме пары правый->левый концы    
;при этом правое число хранится в right
;сделаем вручную
    mov ecx, [k]
    shr dword[arr], cl
    
    mov ebx, [right]
    and ebx, [mask]
    
    mov ecx, 32
    sub ecx, [k]
    shl ebx, cl
    
    or [arr], ebx
;готово
    jmp .out
    
.out_ror:
    mov ecx, [k]
    ror dword[arr], cl 
    
          
.out:    
    mov ecx, 0
.print:
    PRINT_UDEC 4, [arr + 4*ecx]
    PRINT_CHAR ' ' 
    inc ecx
    cmp ecx, dword[N]
    jne .print
    
.return_0:      
    xor eax, eax
    ret