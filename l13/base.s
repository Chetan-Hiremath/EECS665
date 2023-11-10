.globl _start
.text
_start:
        movq $0x7, %rdi
        movq $60, %rax
        syscall
