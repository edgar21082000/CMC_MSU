%include "io.inc"

section .bss
    arr resd 1050000
    ans resd 1
    A resd 1; file *
    B resd 1; file *
    count resd 1; count of elements in file
    head resd 1
    son1 resd 1
    son2 resd 1
    
section .rodata
    LCin_name db "input.bin", 0
    LCout_name db "output.bin", 0
    LCin_format db "rb", 0
    LCout_format db "wb", 0

CEXTERN fopen 
CEXTERN fread
CEXTERN fwrite
CEXTERN fclose

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
    
    ;count = fread(arr, sizeof(int), 1024*1024, A)
    mov dword[esp], arr; int *arr
    mov dword[esp+4], 4; sizeof(int)
    mov dword[esp+8], 1048576; 1024*1024
    mov dword[esp+12], eax; см 33стр
    call fread
    mov [count], eax; вернули кол-во успешно считанных символов  
    
    ;частные случаи из 0 или 1 элемента
    cmp eax, 0
    je .if0
    cmp eax, 1
    je .if1
    ;------------------------------------
                        
    ;по первым двум элементам определи какая потенциально куча
    call ans_maker
    mov dword[ans], eax;
.label_1:; чтобы могли вернуться!

    ;теперь будем проверять массив на условие кучи
;    while(2*i+1 < count){
;		head = ans_key*arr[i];
;		son1 = ans_key*arr[2*i+1];
;		if(2*i+2 >= count) 
;			son2 = head;
;		else
;			son2 = ans_key*arr[2*i+2];
;		
;		if(head > son1 || head > son2){
;			free(arr);
;			return 0;
;		}
;		i++;		
;	}
   
   mov ecx, 0
.while: 
   shl ecx, 1; 2*ecx + 1
   inc ecx
   cmp ecx, [count]
   jge .print
   ;иначе вернем ecx исходное значение
   dec ecx
   shr ecx, 1
   
   mov edx, [ans]; скопировали знак   
   imul edx, dword[arr + 4*ecx]; ans*arr[i]
   mov [head], edx
   
   mov [son2], edx; см 98стр
   
   mov edx, [ans]
   imul edx, [arr + 8*ecx + 4]; ans*arr[2i+1]
   mov [son1], edx
   
   ;проверка и выбор son2 _ if-else 66-68
   ;по умолчанию пусть son2 = head - см 91 стр
   
   shl ecx, 1
   add ecx, 2
   cmp ecx, [count]
   jl .make_son2
.label_2:
   ; теперь проверка условий стр.71
   mov edx, [head]
   cmp edx, [son1]
   jg .return0
   cmp edx, [son2]
   jg .return0 

   inc ecx
   jmp .while
;-----------------------------------------------------


.if0:
    mov dword[ans], 0
    jmp .print

.if1:    
    mov dword[ans], 1
    jmp .print

.make_ans_1:
    mov dword[ans], -1;
    jmp .label_1; вернулись обратно на 60стр

.make_son2:
    sub ecx, 2
    shr ecx, 1
    mov edx, [ans]
    imul edx, [arr + 8*ecx + 8]; ans*arr[2*i+2]
    mov [son2], edx
    jmp .label_2; вернулись обратно в цикл

.return0:
     mov dword[ans], 0
.print:; должны распечатать ans, сделать fclose
    ;B = fopen("output.bin", "wb")
    mov dword[esp], LCout_name
    mov dword [esp+4], LCout_format
    call fopen
    mov dword[B], eax; теперь в [A] лежит file *  
     
    ;fwrite(&ans, sizeof(int), 1, B)
    mov dword[esp], ans
    mov dword[esp+4], 4
    mov dword[esp+8], 1
    mov [esp+12], eax
    call fwrite
    
    ;fclose(B)
    mov eax, dword[B]
    mov [esp], eax
    call fclose
    
    ;fclose(A)
    mov eax, dword[A]
    mov [esp], eax
    call fclose
    
    ;PRINT_DEC 4, ans                
    xor eax, eax
    leave 
    ret

ans_maker:
    mov eax, 1
    mov ecx, 1
    mov edx, [arr]; edx = min = arr[0]
.for:
    cmp edx, [arr + 4*ecx]
    jg .ret_1
    inc ecx
    cmp ecx, [count]
    je .end
    jmp .for
.ret_1:
    mov eax, -1
.end:
    ret