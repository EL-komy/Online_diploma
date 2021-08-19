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

STATE_define(CA_wating)
{
	CA_state_id=CA_wating;
	CA_speed=0;
	CA_distance=gen_random(45,55,1);
	(CA_distance <= CA_threshold)? (CA_state=STATE(CA_wating)):(CA_state=STATE(CA_driving));
	printf("waiting state : distance %d speed=%d\n",CA_distance,CA_speed);

}

STATE_define(CA_driving)
{
	CA_state_id=CA_driving;
	CA_speed=30;
	CA_distance=gen_random(45,55,1);
	(CA_distance <= CA_threshold)? (CA_state=STATE(CA_wating)):(CA_state=STATE(CA_driving));
	printf("driving state : distance %d speed=%d\n",CA_distance,CA_speed);
}

int gen_random(int l,int r,int count)
{
	int i;
	for(i=0;i<count;i++)
	{
		int rum=(rand()%(r-l+1)+l);
		return rum;
	}
}
