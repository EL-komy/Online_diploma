/*
 * US.h
 *
 *  Created on: Jul 13, 2021
 *      Author: Mohamed_ELkomy
 */

#ifndef US_H_
#define US_H_

#include"stdio.h"
#include"stdlib.h"
#include"state.h"

enum{
	US_busy,
}US_state_id;

STATE_define(US_busy);

extern void (*US_state)();
void us_init();
int gen_random(int l,int r,int count);

#endif /* US_H_ */
