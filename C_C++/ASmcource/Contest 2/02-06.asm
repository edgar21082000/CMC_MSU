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
    inc ecx; ������� ��� ��������, ���� ��������� 0
.2_0: ; if (tmp>max) max = tmp
    mov dword[max], ebx
    sub ecx, 1; ���� ecx ���� 0 �� ��������
    je .out

.2: ;(for ecx, ecx!=0, ecx--)   
    mov dword[tmp], eax
    and dword[tmp], edx
    
    dec ecx ; �������� �� ecx-1
    shr dword[tmp], cl; ������� ������� ��������� ����� �� � ���; cl ������� � ecx - ��� ��� ��� ���������
    inc ecx; ��������� ��������� �������� ��������
    
    shr edx, 1; �������� ����� �� 1
    
    mov ebx, dword[tmp]
    cmp ebx, dword[max]; ���������� � ������� ����������
    jge .2_0
    
    sub ecx, 1
    jne .2 ; ���� ecx �� 0 �������� � �����
    
                    
             
.out:
    PRINT_UDEC 4, max
     
    xor eax, eax
    ret