#include"uart.h"

#define UARTdR  *((volatile unsigned int*)((unsigned int *)0x101f1000))

void uart_send_string(unsigned char* ptr)
{
   	while(*ptr !='\0')
	{
		UARTdR =(unsigned char)(*ptr);
		ptr++;
	}
}