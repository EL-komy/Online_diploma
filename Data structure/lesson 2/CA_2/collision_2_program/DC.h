/*
 * DC.h
 *
 *  Created on: Jul 13, 2021
 *      Author: Mohamed_ELkomy
 */

#ifndef DC_H_
#define DC_H_

#include"stdio.h"
#include"stdlib.h"
#include"state.h"

enum{
	DC_idle,
	DC_busy
}DC_state_id;

STATE_define(DC_idle);
STATE_define(DC_busy);
void dc_init();

extern void (*DC_state)();


#endif /* DC_H_ */
