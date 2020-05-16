%include "io.inc"

section .data
    vector dq -86.601, 12.11, 84.4483, -31.1, -76.606, 91.2086, -18.12, -70.73, -0.09922
    n      dd ($-vector)/8

    format db "Valoarea maxima: %f", 10, 0
    max    dq -1000000.0

section .text
global CMAIN
CMAIN:

    mov ecx, dword [n]
    mov eax, vector

repeat:
    cmp ecx, 0
    je done

    fld qword [eax]
    fld qword [max]
    fcomip    ; compara cele doua valori adaugate pe stiva

    ; In acest punct, avem pe stiva FPU doar valoarea din vector (fcomip extrage prima valoare), iar flag-urile din EFLAGS
    ; sunt setate conform comparației.

    ; TODO Verifica rezultatul comparatiei folosind o instructiune conditionala.
    ja mai_mic
    ; TODO Daca valoarea este mai mare decat cea maxima, extrage valoarea de pe stiva in variabila max (hint: fstp).
mai_mare:
    fstp qword [max]
    jmp repeat1
    ; TODO Daca valoarea este mai mica decat cea maxima, doar elibereaza stiva (instructiunea fstp ST0).
mai_mic:
    fstp ST0

repeat1:
    add eax, 8
    dec ecx
    jmp repeat
    je done
    
        
done:

    push dword[max+4]
    push dword[max]
    push format
    call printf
    add esp, 12
    ; TODO Afiseaza rezultatul
    ; TODO Stocheaza valoarea maxima pe stiva. Are 8 octeti, deci sunt necesare doua push-uri.

    xor eax, eax
    ret
