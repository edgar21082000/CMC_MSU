%include "io.inc"

section .bss
    n resd 1
    m resd 1
    k resd 1
    
    i resd 1
    j resd 1
    s resd 1
    
    index_a resd 1
    index_b resd 1
    index_c resd 1
    
    a resd 10000
    b resd 10000; резервируем массивы максимального размера
    c resd 10000
    

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, eax; n
    GET_DEC 4, ebx; m
    GET_DEC 4, ecx; k
    mov [n], eax
    mov [m], ebx
    mov [k], ecx
    
    mov edx, 0; i
    mov edi, 0; j
    mov esi, 0; s
    mov [i], edx
    mov [j], edi
    mov [s], esi
    
    
    ;-----считывание матриц---------
    imul eax, ebx; n*m
    .read_a:
        GET_DEC 4, [a + 4*edi]
        inc edi
        cmp edi, eax
        jne .read_a
        
    mov eax, [n]
    mov edi, [j]
    
    imul ebx, ecx; m*k
    .read_b:
        GET_DEC 4, [b + 4*edi]
        inc edi
        cmp edi, ebx
        jne .read_b
    
    mov ebx, [m]
    mov edi, [j]
    ;--------------------------------
   
    .for:
        ;c[i][j] += a[i][s]*b[s][j]
        mov [index_c], edx
        imul ecx, [index_c]
        add ecx, edi
        mov [index_c] , ecx
        mov ecx, [k]
       
        mov [index_a], edx
        imul ebx, [index_a]
        add ebx, esi
        mov [index_a], ebx
        mov ebx, [m]
        
        mov [index_b], esi
        imul ecx, [index_b]
        add ecx, edi
        mov [index_b], ecx
        mov ecx, [k]
    
        
        mov eax, [index_a]
        mov ebx, [index_b] ; начинаем использовать регистры как временные переменные
        mov ecx, [index_c]
        
        mov edx, [a + 4*eax]
        imul edx, [b + 4*ebx]
        add [c + 4*ecx], edx
        
        mov eax, [n]
        mov ebx, [m] ; возвращаем настоящие занчения регистров
        mov ecx, [k]
        mov edx, [i]
        
        ;начинаем прибавлять индекс s
        inc dword[s]
        mov esi, [s]
        
        cmp esi, ebx
        jne .for
        ; прибавляем индек j и сбрасываем s
        mov dword[s], 0
        mov esi, [s]
        
        inc dword[j]
        mov edi, [j]
        
        cmp edi, ecx
        jne .for
        ; прибавляем индекс i и сбрасываем j
        mov dword[j], 0
        mov edi, [j]
          
        inc edx; i
        inc dword[i]
        
        cmp edx, eax
        jne .for
        mov dword[i], 0
        mov edx, [i]
    ; матрица c сформирована 
    ; распечатаем ее
    
    inc dword[i]
    imul eax, ecx; eax = n*k
    .print:
        PRINT_DEC 4, [c + 4*edx]
        PRINT_CHAR ' '
        inc edx
        cmp edx, ecx
        jne .print
        NEWLINE
        mov ecx, [k]
        inc dword[i]
        imul ecx, [i]
        cmp edx, eax; edx == n*k
        jne .print      
    
    xor eax, eax
    ret