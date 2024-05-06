/*
 * Scheduler.h
 *
 *  Created on: Apr 29, 2024
 *      Author: Elkomy
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "CortexMX_OS_Porting.h"

typedef enum{
	noerror,
	Ready_Queue_init_error,
	Task_exceeded_StackSize
}MYRTOS_error_ID;



typedef struct{
	unsigned int Stack_size;
	unsigned char priority;
	unsigned int _S_PSP_Task ;//Not Entered by the user
	unsigned int _E_PSP_Task ;//Not Entered by the user
	void (*p_tackEntry)(void);
	unsigned char Auto_start;
	unsigned int* current_PSP ;//Not Entered by the user
	char taskName [30];
	enum{
		Suspend,
		Running,
		Waiting,
		ready
	}Task_State;//Not Entered by the user
	struct{
		enum{
			Enable,
			Disable
		}Blocking;
		unsigned int Ticks_count;
	}Timingwaiting;



}Task_ref;

//APIs
MYRTOS_error_ID MYRTOS_init();
MYRTOS_error_ID MYRTOS_Create_Task(Task_ref* Tref );
void MYRTOS_Activate_Task(Task_ref* Tref );
void MYRTOS_Terminate_Task(Task_ref* Tref );

void MYRTOS_StartOS();
void MYRTOS_TaskWait(unsigned int noticks,Task_ref* SelfTref );

#endif /* INC_SCHEDULER_H_ */
