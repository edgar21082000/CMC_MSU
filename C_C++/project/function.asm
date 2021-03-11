extern pow

section .rodata
    const4 dq 4.0
    const2 dq 2.0

section .text
global f1
f1: ;1 + 4/(x^2 +1) 
    push ebp
    mov ebp, esp 
    
    finit
    fld1
    fld qword[const4]
    fld1
    fld qword[ebp+8]
    fld qword[ebp+8]
    fmulp
    faddp
    fdivp
    faddp
    
    leave
    ret
 
global f2       
f2: ;x^3
    push ebp
    mov ebp, esp
    
    finit
    fld qword[ebp+8]
    fld qword[ebp+8]
    fld qword[ebp+8]
    fmulp
    fmulp
    
    leave
    ret
global f3    
f3: ;2^(-x)
    push ebp
    mov ebp, esp
    
    and esp, 0xFFFFFFF0
    sub esp, 16
    
    mov eax, dword[const2]
    mov dword[esp], eax
    mov eax, dword[const2 + 4]
    mov dword[esp+4], eax
    
    finit
    fld qword[ebp+8]
	fchs
    fstp qword[esp+8]
    
    call pow
    
    leave
    ret
    
    
    
    
    
    
    
    