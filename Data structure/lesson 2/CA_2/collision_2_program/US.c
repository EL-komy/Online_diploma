/*
 * US.c
 *
 *  Created on: Jul 13, 2021
 *      Author: Mohamed_ELkomy
 */

#include"US.h"

int US_distance=0;


void (*US_state)();

void us_init()
{
	printf("us_init\n");
}

STATE_define(US_busy)
{
	US_state_id=US_busy;
	printf("US_busy state : distance %d \n",US_distance);
	US_distance=gen_random(45,55,1);
	us_set_dis(US_distance);
	US_state=STATE(US_busy);
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
