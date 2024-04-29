

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



Task_ref task1 ,task2,task3;

void task_1()
{
	while(1)
	{

	}
}

void task_2()
{
	while(1)
	{

	}
}

void task_3()
{
	while(1)
	{

	}
}
int main(void)
{
	MYRTOS_error_ID error;
	//HW int (clock tree, reset controller)
	hw_init();
	if(MYRTOS_init() != noerror)
		while(1);

	task1.Stack_size=1024;
	task1.p_tackEntry=task_1;
	task1.priority=3;
	strcpy(task1.taskName,"task1");

	task2.Stack_size=1024;
	task2.p_tackEntry=task_2;
	task2.priority=3;
	strcpy(task2.taskName,"task2");

	task3.Stack_size=1024;
	task3.p_tackEntry=task_3;
	task3.priority=3;
	strcpy(task3.taskName,"task3");


	error += MYRTOS_Create_Task(&task1);
	error += MYRTOS_Create_Task(&task2);
	error += MYRTOS_Create_Task(&task3);
	while (1)
	{

	}


}
