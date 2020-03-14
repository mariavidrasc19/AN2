%include "io.inc"

section .data
    vector dd 30, 31, 100, 86, 23, 9, 64, 90, 25, 96
    n      dd ($-vector)/4
    format db "Media elementelor: %f", 10, 0

section .text
    global CMAIN

extern printf

CMAIN:
    ; incarca valoarea 0 pe stiva FPU
    fldz

    ; TODO: parcurgerea tuturor elementelor si adunare la valoarea din varful stivei FPU (adunare intreaga)
    mov eax, vector
    mov ecx, dword [n]

    ; TODO: impartirea sumei la numarul de elemente (impartire intreaga)
repeat:
    cmp ecx, 0
    je done
    
    ; aduna la valoarea de pe stiva cate o valoare din vector
    fiadd dword [eax]
    add eax, 4

    dec ecx
    jmp repeat    

    ; TODO Afisarea rezultatului
    ; Rezultatul ar trebui sa fie 55.4

done:
    mov ecx, n
    fidiv dword[ecx]
    sub esp, 8
    fstp qword [esp]

    push format
    call printf
    add esp, 12

    xor eax, eax
    ret
