/*
 * CA.c
 *
 *  Created on: Jul 13, 2021
 *      Author: Mohamed_ELkomy
 */

#include"CA.h"

int CA_speed=0;
int CA_distance=0;
int CA_threshold=50;

void (*CA_state)();

void us_set_dis(int d)
{
	CA_distance=d;
	(CA_distance <= CA_threshold)? (CA_state=STATE(CA_wating)):(CA_state=STATE(CA_driving));
	printf("US-------DINSTANCE=%d-------->CA\n",CA_distance);

}

STATE_define(CA_wating)
{
	CA_state_id=CA_wating;
	CA_speed=0;
	dc_set_speed(CA_speed);
	printf("waiting state : distance %d speed=%d\n",CA_distance,CA_speed);

}

STATE_define(CA_driving)
{
	CA_state_id=CA_driving;
	CA_speed=30;
	dc_set_speed(CA_speed);
	printf("driving state : distance %d speed=%d\n",CA_distance,CA_speed);
}

