.section .text
.global main
.intel_syntax noprefix

main:
	mov rax, 60
	mov rdi, 4
	syscall
