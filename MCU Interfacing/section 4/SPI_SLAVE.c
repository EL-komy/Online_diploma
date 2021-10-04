/*
 * SPI_SLAVE.c
 *
 * Created: 04-Oct-21 2:50:57 PM
 *  Author: Mohamed_ELkomy
 */ 


#define  F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

#define SS   4
#define MOSI 5
#define MISO 6
#define SCK  7

void SPI_SlaveInit()
{
	// Set MOSI, SCK and SS output, all others input
	DDRB |=(1<<MISO) ;
	// Set MISO input
	DDRB &=~(1<<MOSI) &~ (1<<SCK) &~ (1<<SS);
	// Enable SPI
	SPCR =(1<<SPE);
	
}

unsigned char SPI_Slave_Transmit(unsigned char data)
{
	SPDR=data;
	// Wait for transmission complete
	while(!(SPSR &(1<<SPIF)));
	return SPDR;
}

int main(void)
{
	unsigned char sdata;
	SPI_SlaveInit();
	DDRA=0XFF;
	for(sdata=255;sdata>=0;sdata--)
	{
		PORTA=SPI_Slave_Transmit(sdata);
		_delay_ms(500);
	}
}