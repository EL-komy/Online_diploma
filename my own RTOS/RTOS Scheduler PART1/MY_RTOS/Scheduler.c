/*
 * Scheduler.c
 *
 *  Created on: Apr 29, 2024
 *      Author: Elkomy
 */


#include "Scheduler.h"
#include "MYRTOS_FIFO.h"


struct{
	Task_ref* OS_Tasks[100];//Sch. Table
	unsigned int _S_MSP_Task;
	unsigned int _E_MSP_Task;
	unsigned int PSP_Task_Locator;
	unsigned int NO_Active_Task;
	Task_ref* Curren_Task;
	Task_ref* Next_Task;
	enum{
		OSsuspend,
		OsRunning
	}OSmodeID;

}OS_Control;

FIFO_Buf_t Ready_Queue;
Task_ref* Ready_Queue_FIFO[100];
Task_ref IDLE_TASK;



void OS_SVC_Service(int * StackFramePointer)
{
	unsigned char SVC_num;
	SVC_num=    *((unsigned char*)(((unsigned char*)StackFramePointer[6])-2));

	switch(SVC_num)
	{
		case 1:

			break;
		case 2:

				break;
		case 3:

				break;
		case 4:


				break;
	}
}


void PendSV_Handler()
{
	__asm("nop");
}


int OS_SVC_Set(int SVC_ID)
{
	int res ;
	switch (SVC_ID)
	{
	case 1:
		__asm("svc #0x1");
		break;
	case 2:
		__asm("svc #0x2");
			break;
	case 3:
		__asm("svc #0x3");
			break;
	case 4:
			__asm("svc #0x4");
				break;
	}

}




void MYRTOS_Create_MainStack()
{
	OS_Control._S_MSP_Task = _estack;
	OS_Control._E_MSP_Task = OS_Control._S_MSP_Task  - Main_Stack_size;
	//Aligned 8 Bytes spaces between Main Task and PSP tasks
	OS_Control.PSP_Task_Locator = (OS_Control._E_MSP_Task -8);
}

void IDLE_Task(void)
{
	while(1)
		__asm("nop");
}

MYRTOS_error_ID MYRTOS_init()
{
	MYRTOS_error_ID error= noerror;

	//Update OS Mode (OSsuspend)
	OS_Control.OSmodeID= OSsuspend;

	//Specify the MAIN Stack for OS
	MYRTOS_Create_MainStack();
	//Create OS Ready Queue
	if(FIFO_init(&Ready_Queue, Ready_Queue_FIFO, 100) != FIFO_NO_ERROR)
		error += Ready_Queue_init_error;
	//Configure IDLE TASK

	strcpy (IDLE_TASK.taskName, "idleTask");
	IDLE_TASK.priority=255;
	IDLE_TASK.p_tackEntry= IDLE_Task;
	IDLE_TASK.Stack_size=300;

	error += MYRTOS_Create_Task(&IDLE_TASK);


	return error;

}

void MYRTOS_Create_stackoftask(Task_ref* Tref)
{
	/*Task Frame
	 * ======
	 * XPSR
	 * PC (Next Task Instruction which should be Run)
	 * LR (return register which is saved in CPU while TASk1 running before TaskSwitching)
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
	 *====
	 *r5, r6 , r7 ,r8 ,r9, r10,r11 (Saved/Restore)Manual
	 */
	Tref->current_PSP= Tref->_S_PSP_Task;

	Tref->current_PSP--;
	Tref->current_PSP= 0x01000000;  //DUMMY_XPSR should T =1 to avoid BUS fault;//0x01000000

	Tref->current_PSP--;
	Tref->current_PSP= (unsigned int )Tref->p_tackEntry; //pc

	Tref->current_PSP--;
	Tref->current_PSP= 0xFFFFFFFD;//LR = 0xFFFFFFFD (EXC_RETURN)Return to thread with PSP

	for (int  j=0 ; j< 13 ; j++ )
	{
		Tref->current_PSP-- ;
		*(Tref->current_PSP)  = 0 ;

	}
}

MYRTOS_error_ID MYRTOS_Create_Task(Task_ref* Tref )
{
	MYRTOS_error_ID error= noerror;


	//Create Its OWN PSP stack
	//Check task stack size exceeded the PSP stack
	Tref->_S_PSP_Task = OS_Control.PSP_Task_Locator;
	Tref->_E_PSP_Task = Tref->_S_PSP_Task - Tref->Stack_size;
	//	-				-
	//	- _S_PSP_Task	-
	//	-	Task Stack	-
	//	- _E_PSP_Task	-
	//	-				-
	//	- _eheap		-
	//	-				-
	//
	if(Tref->_E_PSP_Task < (unsigned int)(&(_eheap)))
	{
		return Task_exceeded_StackSize ;
	}

	//Aligned 8 Bytes spaces between Task PSP and other
	OS_Control.PSP_Task_Locator = (OS_Control._E_MSP_Task -8);

	//Initialize PSP Task Stack
	MYRTOS_Create_stackoftask(Tref);
	//Task State Update -> Suspend
	Tref->Task_State = Suspend;


	return error;
}
