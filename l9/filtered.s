	.file	"example.cpp"
	.text
	.local	std::__ioinit
	.comm	std::__ioinit,1,1
	.section	.rodata
.LC0:
	.string	"in fn with a\n"
	.text
	.globl	func(int)
	.type	func(int), @function
func(int):
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	std::cout(%rip), %rax
	movq	%rax, %rdi
	call	std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@PLT
	nop
	leave
	ret
	.size	func(int), .-func(int)
	.section	.rodata
.LC1:
	.string	"in fn with a and b\n"
	.text
	.globl	func(int, int)
	.type	func(int, int), @function
func(int, int):
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	leaq	.LC1(%rip), %rax
	movq	%rax, %rsi
	leaq	std::cout(%rip), %rax
	movq	%rax, %rdi
	call	std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@PLT
	nop
	leave
	ret
	.size	func(int, int), .-func(int, int)
	.section	.rodata
.LC2:
	.string	"in fn with c\n"
	.text
	.globl	func(bool)
	.type	func(bool), @function
func(bool):
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	leaq	std::cout(%rip), %rax
	movq	%rax, %rdi
	call	std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@PLT
	nop
	leave
	ret
	.size	func(bool), .-func(bool)
	.globl	main
	.type	main, @function
main:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$1, %edi
	call	func(int)
	movl	$2, %esi
	movl	$1, %edi
	call	func(int, int)
	movl	$1, %edi
	call	func(bool)
	movl	$0, %eax
	popq	%rbp
	ret
	.size	main, .-main
	.type	__static_initialization_and_destruction_0(int, int), @function
__static_initialization_and_destruction_0(int, int):
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L8
	cmpl	$65535, -8(%rbp)
	jne	.L8
	leaq	std::__ioinit(%rip), %rax
	movq	%rax, %rdi
	call	std::ios_base::Init::Init()@PLT
	leaq	__dso_handle(%rip), %rax
	movq	%rax, %rdx
	leaq	std::__ioinit(%rip), %rax
	movq	%rax, %rsi
	movq	std::ios_base::Init::~Init()@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	__cxa_atexit@PLT
.L8:
	nop
	leave
	ret
	.size	__static_initialization_and_destruction_0(int, int), .-__static_initialization_and_destruction_0(int, int)
	.type	_GLOBAL__sub_I__Z4funci, @function
_GLOBAL__sub_I__Z4funci:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$65535, %esi
	movl	$1, %edi
	call	__static_initialization_and_destruction_0(int, int)
	popq	%rbp
	ret
	.size	_GLOBAL__sub_I__Z4funci, .-_GLOBAL__sub_I__Z4funci
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z4funci
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
