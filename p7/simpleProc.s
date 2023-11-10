.data
gbl_a: .quad 0
gbl_main: .quad 0
.align 8
.globl main
.text
main: pushq %rbp # EnterQuad (prologue)
         movq %rsp, %rbp
         addq $16, %rbp
         subq $0, %rsp
#Fn body main
#Fn epilogue main
lbl_0: #leave quad todo
movq $60, %rax
syscall
