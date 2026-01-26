format PE64 console
stack 20000h
entry start

include 'win64a.inc'

section '.text' code executable readable writeable

start:
push 46
call fib
push rax
cinvoke prin, msg, rax
;cinvoke prin, msg+6, qword[cou_]
pop rax
ret

fib:
mov rcx, qword[rsp+8]
cmp rcx, 2
jl .end
push rcx
sub rcx, 2
push rcx
call fib
pop rcx
push rax
dec rcx
push rcx
call fib
pop rcx
add rcx, rax
.end:
mov rax, rcx
;inc qword[cou_]
ret 8

align 10h

data import
library  msvcrt, "msvcrt.dll"
import   msvcrt,  prin, "printf"
end data

align 10h

;cou_  dq 0
msg db "fib = %d", 0Ah, 0Ah, 0

