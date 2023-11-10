.globl _start
.data
var_v: .quad 12

.text
_start: 

         #Function prologue
         pushq %rbp
         movq %rsp, %rbp
         addq $16, %rbp
         subq $16, %rsp

         movq $9, -32(%rbp)

         movq $var_v, %rbx #address of var_v into %rbx
         movq (var_v), %rcx #value of var_v into %rcx

label_1: nop

         movq $60, %rax
         movq $4, %rdi
         syscall