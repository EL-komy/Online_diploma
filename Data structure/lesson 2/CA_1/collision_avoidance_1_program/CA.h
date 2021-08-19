/*
 * CA.h
 *
 *  Created on: Jul 13, 2021
 *      Author: Mohamed_ELkomy
 */

#ifndef CA_H_
#define CA_H_

#include"stdio.h"
#include"stdlib.h"
#include"state.h"

enum{
	CA_wating,
	CA_driving
}CA_state_id;

STATE_define(CA_wating);
STATE_define(CA_driving);
int gen_random(int l,int r,int count);
extern void (*CA_state)();

#endif /* CA_H_ */
