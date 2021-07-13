/*
 * main.c
 *
 *  Created on: Jul 13, 2021
 *      Author: Mohamed_ELkomy
 */

#include"CA.h"
void setup()
{
	CA_state=STATE(CA_wating);
}

void main()
{
	setup();
	while(1)
	{
		CA_state();
	}
}
