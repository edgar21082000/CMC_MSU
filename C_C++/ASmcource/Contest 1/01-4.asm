%include "io.inc"

section .bss
    x resd  1
    n resd  1
    m resd  1
    y resd  1
    diff resd 1
    
section .text
global CMAIN
CMAIN:
    GET_DEC 4, x
    GET_DEC 4, n
    GET_DEC 4, m
    GET_DEC 4, y
    
    mov eax, dword[m]
    sub eax, dword[n]; ��������� ������� ���� � ���
    mov dword[diff], eax
    
    mov eax, dword[y]
    sub eax, 2011
    imul eax, dword[diff]; ��������� ��������� ������� ����
    
    sub dword[x], eax
    PRINT_DEC 4, x
    
    xor eax, eax
    ret