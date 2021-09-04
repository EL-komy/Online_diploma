/*
 * UART.h
 *
 * Created: 01-Sep-21 5:15:17 PM
 *  Author: Mohamed_ELkomy
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
void MCAL_USART_init();
void MCAL_USART_send_char(char data);
char MCAL_USART_receiv_char();
void MCAL_USART_send_string(char *p_data);
char* MCAL_USART_receiv_string();

#endif /* UART_H_ */