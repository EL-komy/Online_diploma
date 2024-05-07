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



typedef enum{
	ActivateTask,
	TerminateTask,
	TaskWaitingtime
}SVC_ID;

FIFO_Buf_t Ready_Queue;
Task_ref* Ready_Queue_FIFO[100];
Task_ref IDLE_TASK;




__attribute ((naked)) void PendSV_Handler()
{
	//====================================
	//Save the Context of the Current Task
	//====================================
	//Get the Current Task "Current PSP from CPU register" as CPU Push XPSR,.....,R0
	OS_GET_PSP(OS_Control.Curren_Task->current_PSP);

	//using this Current_PSP (Pointer) tp store (R4 to R11)
	OS_Control.Curren_Task->current_PSP-- ;
	__asm volatile("mov %0,r4 " : "=r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP-- ;
	__asm volatile("mov %0,r5 " : "=r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP-- ;
	__asm volatile("mov %0,r6 " : "=r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP-- ;
	__asm volatile("mov %0,r7 " : "=r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP-- ;
	__asm volatile("mov %0,r8 " : "=r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP-- ;
	__asm volatile("mov %0,r9 " : "=r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP-- ;
	__asm volatile("mov %0,r10 " : "=r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP-- ;
	__asm volatile("mov %0,r11 " : "=r" (*(OS_Control.Curren_Task->current_PSP))  );

	//save the current Value of PSP
	//already saved in Current_PSP

	//====================================
	//Restore the Context of the Next Task
	//====================================

	OS_Control.Curren_Task= OS_Control.Next_Task;
	OS_Control.Next_Task=NULL;


	__asm volatile("mov r11,%0 " : : "r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP++ ;
	__asm volatile("mov r10,%0 " : : "r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP++ ;
	__asm volatile("mov r9,%0 " : : "r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP++ ;
	__asm volatile("mov r8,%0 " : : "r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP++ ;
	__asm volatile("mov r7,%0 " : : "r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP++ ;
	__asm volatile("mov r6,%0 " : : "r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP++ ;
	__asm volatile("mov r5,%0 " : : "r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP++ ;
	__asm volatile("mov r4,%0 " : : "r" (*(OS_Control.Curren_Task->current_PSP))  );
	OS_Control.Curren_Task->current_PSP++ ;

	//update PSP and exit
	OS_SET_PSP(OS_Control.Curren_Task->current_PSP);
	__asm volatile("BX LR");



}






void MYRTOS_Create_MainStack()
{
	OS_Control._S_MSP_Task =  &_estack;
	OS_Control._E_MSP_Task = OS_Control._S_MSP_Task  - Main_Stack_size;
	//Aligned 8 Bytes spaces between Main Task and PSP tasks
	OS_Control.PSP_Task_Locator = (OS_Control._E_MSP_Task -8);
}

unsigned char ideltaskled;
void IDLE_Task(void)
{

	while(1)
	{
		ideltaskled ^=1;
		__asm("wfe");
	}

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
	*(Tref->current_PSP)= 0x01000000;  //DUMMY_XPSR should T =1 to avoid BUS fault;//0x01000000

	Tref->current_PSP--;
	*(Tref->current_PSP)= (unsigned int )Tref->p_tackEntry; //pc

	Tref->current_PSP--;
	*(Tref->current_PSP)= 0xFFFFFFFD;//LR = 0xFFFFFFFD (EXC_RETURN)Return to thread with PSP

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
	OS_Control.PSP_Task_Locator = (Tref->_E_PSP_Task -8);

	//Initialize PSP Task Stack
	MYRTOS_Create_stackoftask(Tref);
	//Task State Update -> Suspend
	Tref->Task_State = Suspend;
	//Update schudler table
	OS_Control.OS_Tasks[OS_Control.NO_Active_Task]= Tref;
	OS_Control.NO_Active_Task++;

	return error;
}

void bubbleSort()
{
	unsigned int i, j , n;
	Task_ref* temp ;
	n= OS_Control.NO_Active_Task;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++)
			if (OS_Control.OS_Tasks[j]->priority > OS_Control.OS_Tasks[j+1]->priority)
			{
				temp = OS_Control.OS_Tasks[j] ;
				OS_Control.OS_Tasks[j]= OS_Control.OS_Tasks[j+1];
				OS_Control.OS_Tasks[j+1] = temp ;
			}

}
void MYRTOS_Updata_schad_table()
{
	Task_ref* temp =NULL;
	Task_ref* ptask;
	Task_ref* pnexttask;
	int i=0;

	//1- bubble sort SchTable OS_Control-> OSTASKS[100] (priority high then low)
	bubbleSort();
	//2- free Ready Queue
	while(FIFO_dequeue(&Ready_Queue, &temp)!=FIFO_EMPTY );
	//3- update ready queue
	while(i < OS_Control.NO_Active_Task )
	{
		ptask =OS_Control.OS_Tasks[i];
		pnexttask =OS_Control.OS_Tasks[i+1];

		if(ptask->Task_State != Suspend)
		{
			if(pnexttask->Task_State == Suspend)
			{
				FIFO_enqueue(&Ready_Queue, ptask);
				ptask->Task_State =ready;
				break;
			}
			if(ptask->priority < pnexttask->priority)
			{
				FIFO_enqueue(&Ready_Queue, ptask);
				ptask->Task_State =ready;
				break;
			}
			else if (ptask->priority == pnexttask->priority) {
				FIFO_enqueue(&Ready_Queue, ptask);
				ptask->Task_State =ready;
			}
			else if (ptask->priority > pnexttask->priority)
			{
				//not allowed to happen as we already reordered it by bubble sort
				break ;
			}
		}

		i++;
	}

}

void decide_whatnext()
{
	if(Ready_Queue.counter ==0 && OS_Control.Curren_Task->Task_State != Suspend)
	{
		OS_Control.Curren_Task->Task_State= Running;
		FIFO_enqueue(&Ready_Queue, OS_Control.Curren_Task);
		OS_Control.Next_Task = OS_Control.Curren_Task;
	}
	else
	{
		FIFO_dequeue(&Ready_Queue, &OS_Control.Next_Task);
		OS_Control.Next_Task->Task_State=Running;

		if( (OS_Control.Curren_Task->priority == OS_Control.Next_Task->priority)  && (OS_Control.Curren_Task->Task_State != Suspend))
		{
			FIFO_enqueue(&Ready_Queue, OS_Control.Curren_Task);
			OS_Control.Curren_Task->Task_State=ready;
		}
	}

}

void OS_SVC_Service(int * StackFramePointer)
{
	unsigned char SVC_num;
	SVC_num=    *((unsigned char*)(((unsigned char*)StackFramePointer[6])-2));

	switch(SVC_num)
	{
	case ActivateTask:
	case TerminateTask:
		//Update Sch Table, Ready Queue
		MYRTOS_Updata_schad_table();
		//OS is in Running State
		if(OS_Control.OSmodeID == OsRunning)
		{
			if(strcmp(OS_Control.Curren_Task ->taskName ,"idleTask"))
			{
				decide_whatnext();

				trigger_os_pendsv();
			}

		}

		break;
	case TaskWaitingtime:
		MYRTOS_Updata_schad_table();

		break;
	}
}



void MYRTOS_OS_SVC_Set(SVC_ID ID)
{
	switch (ID)
	{
	case ActivateTask:
		__asm("svc 0x0");
		break;
	case TerminateTask:
		__asm("svc 0x01");
		break;
	case TaskWaitingtime:
		__asm("svc 0x02");
		break;
	}

}

void MYRTOS_Activate_Task(Task_ref* Tref )
{
	Tref->Task_State=Waiting;
	MYRTOS_OS_SVC_Set(ActivateTask);
}
void MYRTOS_Terminate_Task(Task_ref* Tref )
{
	Tref->Task_State=Suspend;
	MYRTOS_OS_SVC_Set(TerminateTask);

}

void MYRTOS_TaskWait(unsigned int noticks,Task_ref* SelfTref )
{
	SelfTref->Timingwaiting.Blocking=Enable;
	SelfTref->Timingwaiting.Ticks_count=noticks;
	// Task Should be blocked
	SelfTref->Task_State=Suspend;
	//to be suspended immediately
	MYRTOS_OS_SVC_Set(TerminateTask);
}

void MYRTOS_StartOS()
{
	OS_Control.OSmodeID=Running;
	//Set Default "Current Task =Idle Task"
	OS_Control.Curren_Task=&IDLE_TASK;
	//Activate IDLE Task
	MYRTOS_Activate_Task(&IDLE_TASK);
	//Start Ticker
	Start_Ticker(); // 1ms

	OS_SET_PSP(OS_Control.Curren_Task->current_PSP);

	//Switch Thread Mode SP from MSP to PSP
	OS_SWITCH_SP_TO_PSP;
	OS_SWITCH_ACCESS_TO_UNPRI;
	IDLE_TASK.p_tackEntry();


}

void MYRTOS_Updata_Waitingtime()
{
	for (int i=0;i<OS_Control.NO_Active_Task;i++)
	{
		if(OS_Control.OS_Tasks[i]->Task_State== Suspend)
		{
			if(OS_Control.OS_Tasks[i]->Timingwaiting.Blocking== Enable)
			{
				OS_Control.OS_Tasks[i]->Timingwaiting.Ticks_count--;
				if(OS_Control.OS_Tasks[i]->Timingwaiting.Ticks_count== 0)
				{
					OS_Control.OS_Tasks[i]->Timingwaiting.Blocking= Disable;
					OS_Control.OS_Tasks[i]->Task_State=Waiting ;
					MYRTOS_OS_SVC_Set(TaskWaitingtime);
				}
			}
		}
	}
}

