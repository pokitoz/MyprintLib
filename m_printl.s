.section .data
	string:	.ascii	"Data test\n"
	#Size of the string	
	length:	.quad	. - string

.section .text
.global m_puts_asm
.type print, @function

# Parameters: 
#	characters 	-> %r
#	size		-> %

m_puts_asm:
	#Write syscall
	movq	$0x1, %rax
	
	#The length of the string
	movq	%rsi, %rdx
		
	#The string to write
	movq	$string, %rsi
	#movq	%esi, %rsi

	#File descriptor (stdout is 0)	
	movq	$0x1, %rdi
	syscall           
	

	#Return the number of character written
	movq    %rax,%rdi
	# Move 60(sys_exit) into rax
	movq	$0x3c,%rax
	syscall
