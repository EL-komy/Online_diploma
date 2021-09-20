/*
 * GccApplication1.c
 *
 * Created: 02-Sep-21 2:16:51 AM
 *  Author: Mohamed_ELkomy
 */ 


#include "MCAL/UART.h"
#include "HAL/lcd.h"

int main(void)
{
	char *dat;
	LCD_INIT();
	MCAL_USART_init();
	MCAL_USART_send_char('A');
	MCAL_USART_send_char('M');
	
	MCAL_USART_send_string(" fff");
	dat=MCAL_USART_receiv_string();
	LCD_WRITE_STRING(dat);
	
	while(1)
	{
		
	}
}