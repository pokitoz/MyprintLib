#include<stdio.h> 
#include<stdarg.h>						

void m_printf(char *,...);


int main(void) 
{ 
	m_printf("My printf", 9);

	//register int counter asm("rdi");
	//counter = 120;
	
	return 0;
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


void m_printf(char* format,...) 
{ 
	char *character; 
	unsigned int i; 
	char *s; 
	
	va_list arg; 
	va_start(arg, format); 
	
	for(character = format; *character != '\0'; character++) 
	{ 
		while( *character != '%' ) 
		{ 
			m_putchar(*character);
			character++; 
		} 
		
		character++; 
		
		switch(*character) 
		{ 
			case 'c' : 
				i = va_arg(arg, int);
				break; 
						
			case 'd' : 
				i = va_arg(arg, int);
				if(i<0) 
				{ 
				} 
				break; 
						
			case 'o': 
				i = va_arg(arg, unsigned int);
				break; 
						
			case 's': 
				s = va_arg(arg, char*);
				break; 
						
			case 'x': 
				i = va_arg(arg, unsigned int);
				break; 
		}	
	} 
	
	va_end(arg); 
} 
