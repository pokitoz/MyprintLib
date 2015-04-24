#include<stdio.h> 
#include<stdarg.h>						

extern int m_puts_asm(char* characters, int size);

void m_puts(char *str);
void m_putchar(const char c);
void m_printf(char *format,...);

int main(void) 
{ 

	char* s = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n";
	m_printf("Hello hello %s", s);

	//register int counter asm("rdi");


	m_printf("END\n");
	
	return 0;
} 



void m_puts(char *str){
	
	int size = 0;
	while(str[size] != '\0'){
		size = size +1;
	}

	char* s = "aaaaaaaaaaa";
	m_puts_asm(s, size);

	
	printf("\nSize- %d\n", size);
	register int counter asm("rdx");
	counter = size;

	__asm__ __volatile__	(
		//Write syscall
		"movq $1, %%rax\n\t"
		//File descriptor (stdout is 0)		
		"movq $0, %%rdi\n\t"
		//The string to write
		"movq %[character], %%rsi\n\t"
		//Number of characters
		//"movq %[ssize], %%rdx\n\t"
		"syscall\n\t"
		: // 0 output
		: [character] "g" ( str ) //, [ssize] "g" (size)
		: "%rax", "%rdi", "%rsi", "%rdx"
	);

	

}


void m_putchar(const char c){
	//Inline Assembly
/*
	asm("movq %[xx], %%rdi\n\t"
	"call putchar\n\t"
	:	
	: [xx] "g" (c)
	: "%rdi"
    	);
*/
	asm(
		"movq $1, %%rax\n\t"
		"movq $0, %%rdi\n\t"
		"movq %[character], %%rsi\n\t"
		"movq $1, %%rdx\n\t"
		"syscall"		
		:	
		: [character] "g" (&c)
		: "%rax", "%rdi", "%rsi", "%rdx"
		
	);

	
}


void m_printf(char *format,...) 
{ 
	char *character;
	unsigned int in; 
	char *s_in; 
	
	va_list arg; 
	va_start(arg, format); 
	character = format;
	while(*character != '\0') 
	{ 
		while( *character != '%' ) 
		{ 
			m_putchar(*character);
			character++; 
		} 
		
		character++; 
		
		switch(*character) 
		{
			case 'c':
				in = va_arg(arg, int);
				m_putchar(in);
				break; 
						
			case 'd': 
				in = va_arg(arg, int);
				if(in<0) 
				{ 
				} 
				break; 
						
			case 'o': 
				in = va_arg(arg, unsigned int);
				break; 
						
			case 's': 
				s_in = va_arg(arg, char*);
				m_puts(s_in);
				break; 
						
			case 'x': 
				in = va_arg(arg, unsigned int);
				
				m_putchar(in);
				break; 
		}

		 character++;	
	} 
	
	va_end(arg); 
} 
