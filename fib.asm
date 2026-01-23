format PE64 console

include 'win64a.inc'

sub rsp, 20h

push 46
call fib

push rax
invoke prin, msg, rax
pop rax


add rsp, 20h
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
ret 8

msg db 0ah, 'fib = %d', 0ah, 0ah, 0

align 10h

data import

library msvcrt, 'msvcrt.dll'

import msvcrt, prin, 'printf'

end data