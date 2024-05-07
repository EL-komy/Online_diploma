

#include <stdint.h>
#include "core_cm3.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "STM32F103x8.h"
#include "stm32f103x8_gpio_driver.h"
#include "lcd.h"
#include "keypad.h"
#include "stm32f103x8_EXTI_driver.h"
#include "stm32f103x8_USART_driver.h"
#include "stm32f103x8_SPI_driver.h"
#include "stm32f103x8_I2C_driver.h"
#include "I2C_Slave_EEPROM.h"

#include "Scheduler.h"



Task_ref task1 ,task2,task3,task4;
Mutex_ref mutex1, mutex2;
unsigned char laod[3]={1,2,3};
unsigned char laod2[3]={1,2,3};

unsigned char task1led,task2led,task3led,task4led;

void task_1()
{
	static int i=0;
	while(1)
	{
		task1led ^=1;
		i++;
		if(i==100)
		{
	//		MYRTOS_AquireMutex(&mutex1, &task1);
			MYRTOS_Activate_Task(&task2);
	//		MYRTOS_AquireMutex(&mutex2 , &task1);
		}
		if(i==200)
		{
			i=0;
			MYRTOS_ReleaseMutex(&mutex1);
		}


	}
}

void task_2()
{
	static int i=0;
	while(1)
	{
		task2led ^=1;
		i++;
		if(i==100)
		{
			MYRTOS_Activate_Task(&task3);
		}
		if(i==200)
		{
			i=0;
			MYRTOS_Terminate_Task(&task2);
		}


	}
}

void task_3()
{
	static int i=0;
	while(1)
	{
		task3led ^=1;
		i++;
		if(i==100)
		{
			MYRTOS_Activate_Task(&task4);
		}
		if(i==200)
		{
			i=0;
			MYRTOS_Terminate_Task(&task3);
		}


	}
}

void task_4()
{
	static int i=0;
	while(1)
	{
		task4led ^=1;
		i++;
		if(i==3)
		{
		//	MYRTOS_AquireMutex(&mutex2, &task4);
//			MYRTOS_AquireMutex(&mutex1, &task4);
		}
		if(i==200)
		{
			i=0;
			MYRTOS_ReleaseMutex(&mutex1);
			MYRTOS_Terminate_Task(&task4);
		}
	}
}

int main(void)
{
	MYRTOS_error_ID error;
	//HW int (clock tree, reset controller)
	hw_init();
	if(MYRTOS_init() != noerror)
		while(1);
	mutex1.payload_size=3;
	mutex1.Ppayload = laod;
	strcpy(mutex1.mutex_name,"mutex_t1_t4");

	mutex2.payload_size=3;
	mutex2.Ppayload = laod2;
	strcpy(mutex2.mutex_name,"mutex2_t1_t4");

	task1.Stack_size=512;
	task1.p_tackEntry=task_1;
	task1.priority=4;
	strcpy(task1.taskName,"task1");

	task2.Stack_size=512;
	task2.p_tackEntry=task_2;
	task2.priority=3;
	strcpy(task2.taskName,"task2");

	task3.Stack_size=512;
	task3.p_tackEntry=task_3;
	task3.priority=2;
	strcpy(task3.taskName,"task3");


	task4.Stack_size=512;
	task4.p_tackEntry=task_4;
	task4.priority=1;
	strcpy(task4.taskName,"task4");


	error += MYRTOS_Create_Task(&task1);
	error += MYRTOS_Create_Task(&task2);
	error += MYRTOS_Create_Task(&task3);
	error += MYRTOS_Create_Task(&task4);

	MYRTOS_Activate_Task(&task1);


	MYRTOS_StartOS();

	while (1)
	{

	}


}
