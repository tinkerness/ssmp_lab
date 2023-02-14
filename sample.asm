assume cs:code,ds:data
data segment
msg db 'hello$'
data ends
code segment
start: mov ax,data
    mov ds,ax
    mov dx,offset msg
    mov ah,09h
    int 21h
    mov ah,4ch
    int 21h
code ends
end start

 COMMENT @
 output:-
 hello
 @
