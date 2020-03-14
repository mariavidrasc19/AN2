%include "io.inc"

extern getAST
extern freeAST

section .bss
    ; La aceasta adresa, scheletul stocheaza radacina arborelui
    root: resd 1

section .text
global main
myATOI:  ; din string in numar
    push ebp
    mov ebp, esp
    
    ; in edx pastram rezultatul
    mov edx, 0
    
    ; in ebx pastram semnul
    mov ebx, 1 
    
    ; extragem primul byte si verificam daca e minus
    movzx ecx, byte [eax]
    cmp ecx, '-'
    je treatMinus
    
myLoop:
    cmp ecx, 0
    je loopExit
    
    sub ecx, '0' ; transformam din caracter in numar
    
    imul edx, 10
    add edx, ecx
    
    ; ne mutam la urmatorul caracter
    add eax, 1
    movzx ecx, byte [eax] 
    jmp myLoop
    
treatMinus: 
    ; pastram minusul
    mov ebx, -1
    
    ; ne mutam la urmatorul caracter  
    add eax, 1
    movzx ecx, byte [eax]   
    jmp myLoop
    
loopExit:
    ; aplicam semnul rezultatului
    imul edx, ebx
    
    leave
    ret
    
parcurgere:
    push ebp
    mov ebp, esp
    
    ; Nota: in edx o sa tinem rezultatul evaluarii
    ; alta nota: 10
    
    ; in ebx avem nodu
    mov ebx, [ebp + 8]
    
    ; punem valoarea nodului pe stiva
    mov eax, [ebx]
    push eax
    
    ; verificam daca nodul e frunza / contine numar
    mov ebx, [ebx + 4]
    cmp ebx, 0
    je sunt_numar
    
    ; evaluam nodul din stanga
    push ebx
    call parcurgere
    pop ebx
    
    ; salvam rezultatul evaluarii nodului din stanga pe stiva
    push edx
    
    ; evaluam nodul din dreapta
    mov ebx, [ebp + 8]
    mov ebx, [ebx + 8]
    push ebx
    call parcurgere
    pop ebx
    
    ; salvam rezultatul nodului din dreapta in ecx
    mov ecx, edx
    
    ; extragem rezultatul nodului din stanga in edx
    pop edx
    
    ; extragem valoarea nodului in eax
    pop eax
    mov eax, [eax]
    
    ; evaluam nodul curent in functie de operatii
    cmp eax, '+'
    je adunare
    
    cmp eax, '-'
    je scadere
    
    cmp eax, '*'
    je inmultire
    
    cmp eax, '/'
    je impartire
    
adunare:
    add edx, ecx    
    jmp exit_parcurgere
scadere:
    sub edx, ecx  
    jmp exit_parcurgere
inmultire:
    imul edx, ecx    
    jmp exit_parcurgere
impartire:
    mov eax, edx
    cdq
    idiv ecx
    mov edx, eax
    jmp exit_parcurgere
    
sunt_numar:
    call myATOI
    
exit_parcurgere:
    leave
    ret
    
main:
    mov ebp, esp; for correct debugging
    ; NU MODIFICATI
    push ebp
    mov ebp, esp
    
    ; Se citeste arborele si se scrie la adresa indicata mai sus
    call getAST
    mov [root], eax
    
    ; Implementati rezolvarea aici
    push dword [root]
    
    ; evaluam copacul
    call parcurgere
    
    PRINT_DEC 4, edx
    NEWLINE
 
    ; NU MODIFICATI
    ; Se elibereaza memoria alocata pentru arbore
    push dword [root]
    call freeAST
    
    xor eax, eax
exit:
    leave
    ret