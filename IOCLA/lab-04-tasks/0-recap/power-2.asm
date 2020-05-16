%include "io.inc"

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    mov eax, 211    ; to be broken down into powers of 2
    mov ebx, 1      ; stores the current power

    ; TODO - print the powers of 2 that generate number stored in EAX
loop:
    cmp ebx, eax
    ja gata

    PRINT_DEC 4, ebx
    NEWLINE
    
    add ebx, ebx
    jmp loop
    
gata:
    leave
    ret
