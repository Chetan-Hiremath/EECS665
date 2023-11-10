.data
gbl_main: .quad 0
.align 8
.globl main
.text
main: pushq %rbp # EnterQuad (prologue)
         movq %rsp, %rbp
         addq $16, %rbp
         subq $16, %rsp
#Fn body main
#            [a] := 4
movq $4, %rax
