/*
 * DC.c
 *
 *  Created on: Jul 13, 2021
 *      Author: Mohamed_ELkomy
 */

#include"DC.h"

int DC_speed=0;

void (*DC_state)();

void dc_init()
{
	printf("dc_init\n");
}

void dc_set_speed(int s)
{
	DC_speed=s;
	DC_state=STATE(DC_busy);
	printf("CA -----SPEED=%d---> DC\n",DC_speed);
}

STATE_define(DC_idle)
{
	DC_state_id=DC_idle;
	DC_state=STATE(DC_idle);
	printf("DC_idle state : speed=%d\n",DC_speed);

}

STATE_define(DC_busy)
{
	DC_state_id=DC_busy;
	DC_state=STATE(DC_idle);
	printf("DC_busy state : speed=%d\n",DC_speed);
}
