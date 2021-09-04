
#include "UART.h"

MCAL_USART_init()
{
	//baud rate 9600 at 8M HZ
	UBRRL=51;
	//Asynchronous Operation
	UCSRC |=(1<<URSEL);
	UCSRC &=~(1<<UMSEL);
	//NO parity mode
	UCSRC &=~(1<<UPM0);
	UCSRC &=~(1<<UPM1);
	//NUMBER OF STOP BITS
	UCSRC &=~(1<<USBS);
	//NORMAL mode
	UCSRA &=~(1<<U2X);
	
	//Enable
	UCSRB |=(1<<RXEN);
	UCSRB |=(1<<TXEN);
	
	//Character Size 8 BITS
	UCSRC |=(1<<UCSZ0);
	UCSRC |=(1<<UCSZ1);
}

void MCAL_USART_send_char(char data)
{
	while(( !( UCSRA & (1<<UDRE)) ));
	UDR=data;
}
char MCAL_USART_receiv_char()
{
	while(( !( UCSRA & (1<<RXC)) ));
	return UDR;
}

void MCAL_USART_send_string(char *p_data)
{
	while(*p_data != '\0')
	{
		MCAL_USART_send_char(*p_data);
		p_data++;
	}
}


char* MCAL_USART_receiv_string()
{
	char data[50],i;
	char get =MCAL_USART_receiv_char();
	for(i=0;get !='#';i++)
	{
		data[i]=get;
		get =MCAL_USART_receiv_char();
	}
	data[i]='\0';
	return data;
}
