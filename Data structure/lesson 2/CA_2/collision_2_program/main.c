/*
 * main.c
 *
 *  Created on: Jul 13, 2021
 *      Author: Mohamed_ELkomy
 */

#include"CA.h"
#include"US.h"
#include"DC.h"
void setup()
{
	CA_state=STATE(CA_wating);
	US_state=STATE(US_busy);
	CA_state=STATE(DC_idle);
	us_init();
	dc_init();
}

void main()
{
	setup();
	volatile int i;
	while(1)
	{
		US_state();
		CA_state();
		DC_state();
		for(i=0;i<2000;i++);
	}
}
