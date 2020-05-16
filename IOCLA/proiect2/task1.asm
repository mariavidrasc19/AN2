%include "include/io.inc"

extern atoi
extern printf
extern exit

; Functions to read/free/print the image.
; The image is passed in argv[1].
extern read_image
extern free_image
; void print_image(int* image, int width, int height);
extern print_image

; Get image's width and height.
; Store them in img_[width, height] variables.
extern get_image_width
extern get_image_height

section .data
	use_str db "Use with ./tema2 <task_num> [opt_arg1] [opt_arg2]", 10, 0

section .bss
    task:       resd 1
    img:        resd 1
    img_width:  resd 1
    img_height: resd 1

section .text
global main

; task 1
baby1:
    mov esi, [img]
    
    mov ecx, 0

; se ia fiecare linie din matrice    
linii:
    cmp ecx, [img_height]
    je schimbare_cheie
    
    mov edx, 0 ; tine contorul 
    mov ebx, 0
    call coloane
    
    inc ecx
    jmp linii
    
; se ia fiecare 4 octeti din linia ecx din matrice 
coloane:
    cmp edx, [img_width]
    je afara
    
    mov eax, DWORD [esi]
    xor eax, edi
 
    jmp verificare_char
    
continuare:
    cmp ebx, 6
    je printare
    
    add esi, 4
    
    inc edx
    jmp coloane

schimbare_cheie:
    inc edi
    jmp baby1


printare:
    mov esi, [img]
    mov eax, 4
    imul eax, ecx
    imul eax, [img_width]
    add esi, eax
    
    mov eax, 0
myloop:
    cmp eax, 40
    je mai_departe
    
    mov ebx, DWORD [esi]
    xor ebx, edi
    PRINT_CHAR ebx
    
    add esi, 4
    inc eax
    jmp myloop
mai_departe:
    NEWLINE
    PRINT_DEC 4, edi
    NEWLINE
    PRINT_DEC 4, ecx
    jmp gata

verificare_char:
    cmp ebx, 0
    je if_r
    cmp ebx, 1
    je if_e
    cmp ebx, 2
    je if_v
    cmp ebx, 3
    je if_i
    cmp ebx, 4
    je if_e   
    cmp ebx, 5
    je if_n
    cmp ebx, 6
    je if_t
    jmp afara
if_r:
    cmp eax, 'r'
    je e_ce_trebe
    jmp nu
if_e:
    cmp eax, 'e'
    je e_ce_trebe
    jmp nu
if_v:
    cmp eax, 'v'
    je e_ce_trebe
    jmp nu
if_i:
    cmp eax, 'i'
    je e_ce_trebe
    jmp nu
if_a:
    cmp eax, 'a'
    je e_ce_trebe
    jmp nu
if_n:
    cmp eax, 'n'
    je e_ce_trebe
    jmp nu
if_t:
    cmp eax, 't'
    je e_ce_trebe
    jmp nu
e_ce_trebe:
    cmp ebx, 6
    je continuare
    inc ebx
    jmp continuare 
nu:
    mov ebx, 0
    jmp continuare
    
afara:
    ret
; gata task 1

        
main:
    mov ebp, esp; for correct debugging
    ; Prologue
    ; Do not modify!
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]
    cmp eax, 1
    jne not_zero_param

    push use_str
    call printf
    add esp, 4

    push -1
    call exit

not_zero_param:
    ; We read the image. You can thank us later! :)
    ; You have it stored at img variable's address.
    mov eax, [ebp + 12]
    push DWORD[eax + 4]
    call read_image
    add esp, 4
    mov [img], eax

    ; We saved the image's dimensions in the variables below.
    call get_image_width
    mov [img_width], eax

    call get_image_height
    mov [img_height], eax

    ; Let's get the task number. It will be stored at task variable's address.
    mov eax, [ebp + 12]
    push DWORD[eax + 8]
    call atoi
    add esp, 4
    mov [task], eax

    ; There you go! Have fun! :D
    mov eax, [task]
    cmp eax, 1
    je solve_task1
    cmp eax, 2
    je solve_task2
    cmp eax, 3
    je solve_task3
    cmp eax, 4
    je solve_task4
    cmp eax, 5
    je solve_task5
    cmp eax, 6
    je solve_task6
    jmp done

solve_task1:
    ; TODO Task1
    mov edi, 0
    call baby1
gata:
    jmp done
solve_task2:
    ; TODO Task2
    jmp done
solve_task3:
    ; TODO Task3
    jmp done
solve_task4:
    ; TODO Task4
    jmp done
solve_task5:
    ; TODO Task5
    jmp done
solve_task6:
    ; TODO Task6
    jmp done

    ; Free the memory allocated for the image.
done:
    push DWORD[img]
    call free_image
    add esp, 4

    ; Epilogue
    ; Do not modify!
    xor eax, eax
    leave
    ret
    
       
_start:
    mov     esi, img                      ; get pointer to array
    mov     edi, [img_width]               ; edi = number of array elements
    sub edi, 1
.PrintArray:
    mov     edx, 1                          ; print 1 byte                 
    mov     ecx, [esi] 
    PRINT_UDEC 1, ecx
    PRINT_CHAR ' '

    add     esi, 4                          ; get next element, 4 because it's an array of dwords
    dec     edi                             ; decrease loop counter
    jns     .PrintArray                     ; if edi ! -1 continue loop
    call exit