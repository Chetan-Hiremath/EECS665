.data
bytes: .byte 0x48, 0xc7, 0xc7, 0x0f, 0x00, 0x00, 0x00, 0x48, 0xc7, 0xc0, 0x3c, 0x00, 0x00, 0x00, 0x0f, 0x05
len: .quad 16

.globl _start
.text
_start:
        movq $nops, %rax
        movq $bytes, %rbx
        movq (len), %rdx
        
loader:
        cmpq $0, %rdx
        je nops
        
        movb (%rbx), %cl
        movb %cl, (%rax)
        addq $1, %rax
        addq $1, %rbx
        subq $1, %rdx
        jmp loader

nops:
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
