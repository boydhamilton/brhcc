
; to compile
; nasm -felf64 test.s
; ld -o test.exe test.o

global _start
_start:
	mov rax, 60 	; syscall 60 is the exit syscall
	mov rdi, 1  	; what our exit syscall will return
	syscall		; calls the syscall we've loaded into rax
