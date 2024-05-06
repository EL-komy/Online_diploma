

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
unsigned char task1led,task2led,task3led,task4led;

void task_1()
{
	static int i=0;
	while(1)
	{
		task1led ^=1;
		i++;
		if(i==30)
		{
			MYRTOS_Activate_Task(&task4);
			MYRTOS_TaskWait(100,&task1);
			i=0;
		}


	}
}

void task_2()
{
	while(1)
	{
		task2led ^=1;
		MYRTOS_TaskWait(300,&task2);

	}
}

void task_3()
{
	while(1)
	{
		task3led ^=1;
		MYRTOS_TaskWait(500,&task3);

	}
}

void task_4()
{
	static int i=0;
	while(1)
	{
		task4led ^=1;
		MYRTOS_TaskWait(1000,&task4);


	}
}

int main(void)
{
	MYRTOS_error_ID error;
	//HW int (clock tree, reset controller)
	hw_init();
	if(MYRTOS_init() != noerror)
		while(1);

	task1.Stack_size=512;
	task1.p_tackEntry=task_1;
	task1.priority=3;
	strcpy(task1.taskName,"task1");

	task2.Stack_size=512;
	task2.p_tackEntry=task_2;
	task2.priority=3;
	strcpy(task2.taskName,"task2");

	task3.Stack_size=512;
	task3.p_tackEntry=task_3;
	task3.priority=3;
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
	MYRTOS_Activate_Task(&task2);
	MYRTOS_Activate_Task(&task3);

	MYRTOS_StartOS();

	while (1)
	{

	}


}
