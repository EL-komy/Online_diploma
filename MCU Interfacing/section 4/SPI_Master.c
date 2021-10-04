/*
 * SPI_Master.c
 *
 * Created: 04-Oct-21 2:32:01 PM
 *  Author: Mohamed_ELkomy
 */ 

#define  F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

#define SS   4
#define MOSI 5
#define MISO 6
#define SCK  7

void SPI_MasterInit()
{
	// Set MOSI, SCK and SS output, all others input 
	DDRB |=(1<<MOSI) | (1<<SCK) | (1<<SS);
	// Set MISO input 
	DDRB &=~(1<<MISO);
	// Enable SPI, Master, set clock rate fck/16 
	SPCR =(1<<SPE) |(1<<MSTR) |(1<<SPR0);
	
}

unsigned char SPI_Master_Transmit(unsigned char data)
{
	SPDR=data;
	// Wait for transmission complete 
	while(!(SPSR &(1<<SPIF)));
	return SPDR;
} 

int main(void)
{
    unsigned char mdata;
	SPI_MasterInit();
	DDRA=0XFF;
	for(mdata=0;mdata<255;mdata++)
	{
		PORTA=SPI_Master_Transmit(mdata);
		_delay_ms(500);
	}
}