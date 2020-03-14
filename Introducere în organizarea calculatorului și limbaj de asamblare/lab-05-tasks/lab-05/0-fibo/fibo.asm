%include "io.inc"
section .data
    N dd 9 ; compute the sum of the first N fibonacci numbers
    
section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    ; TODO: calculate the sum of first N fibonacci numbers
    ;       (f(0) = 0, f(1) = 1)
    ;       store the sum in eax
    ;       use loop instruction 
    mov ecx, [N]
    xor eax, eax
    mov edx, 1
    mov ebx, 1
    
label:
    cmp ecx, 0
    jna print
    
    add eax, edx
    add eax, ebx
    
    mov edx, ebx
    mov ebx, eax
    
    dec ecx
    jmp label
    
print:

    PRINT_STRING "Sum first "
    PRINT_DEC 4, [N]
    PRINT_STRING " fibo is "
    PRINT_UDEC 4, eax

    xor eax, eax
    leave
	ret
