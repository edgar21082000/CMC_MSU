extern pow 

section .rodata
    const2 dq 2.0
    const3 dq 3.0
    const_8 dq -8.0
     
    
section .text
global df1
df1: ; -8x/(x^2+1)^2
    push ebp
    mov ebp, esp 
    
    finit
    fld qword[const_8]
    fld qword[ebp+8]
    fmulp
	
	fld1
    fld qword[ebp+8]
    fld qword[ebp+8]
    fmulp
    faddp
    fdivp
	
	fld1
    fld qword[ebp+8]
    fld qword[ebp+8]
    fmulp
    faddp
	fdivp
    
    leave
    ret

global df2   
df2: ;3x^2
    push ebp
    mov ebp, esp
    
    finit
    fld qword[const3]
    fld qword[ebp+8]
    fmulp
	fld qword[ebp+8]
    fmulp
    
    leave
    ret
    
global df3    
df3: ;-2^(-x)*ln(2)
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
	
	fchs
	fldln2
	fmulp
    
    leave
    ret
    
    
    
    
    
    
    
    