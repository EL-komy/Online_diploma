/*
 * state.h
 *
 *  Created on: Jul 13, 2021
 *      Author: Mohamed_ELkomy
 */

#ifndef STATE_H_
#define STATE_H_

#define STATE_define(stat) void st_##stat()
#define STATE(state) st_##state

void us_set_dis(int d);
void dc_set_speed(int s);



#endif /* STATE_H_ */
