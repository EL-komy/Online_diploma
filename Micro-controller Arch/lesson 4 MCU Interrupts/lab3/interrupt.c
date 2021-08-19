/*
 * interrupt.c
 *
 * Created: 08-Aug-21 2:09:45 PM
 *  Author: Mohamed_ELkomy
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
int main(void)
{
	SREG |=(1<<7);
	sei();
	//enable an external output
	GICR |=(1<<5);
	GICR |=(1<<6);
	GICR |=(1<<7);
	//make pin input
	DDRB &=~(1<<2);
	DDRD &=~(1<<2);
	DDRD &=~(1<<3);
	//make pin output
	DDRD |=(1<<5);
	DDRD |=(1<<6);
	DDRD |=(1<<7);
	
	MCUCR |=13;
	MCUCSR &=~(1<<6);
    while(1);
}

ISR(INT0_vect)
{
	PORTD |=(1<<5);
	_delay_ms(1000);
	PORTD &=~(1<<5);
	//GIFR |=(1<<6);
}

ISR(INT1_vect)
{
	PORTD |=(1<<6);
	_delay_ms(1000);
	PORTD &=~(1<<6);
	//GIFR |=(1<<7);
}

ISR(INT2_vect)
{
	PORTD |=(1<<7);
	_delay_ms(1000);
	PORTD &=~(1<<7);
	//GIFR |=(1<<5);
}