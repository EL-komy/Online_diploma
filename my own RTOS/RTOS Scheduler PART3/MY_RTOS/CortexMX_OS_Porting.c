/*
 * CortexMX_OS_Porting.c
 *
 *  Created on: Apr 29, 2024
 *      Author: Elkomy
 */



#include "CortexMX_OS_Porting.h"

unsigned char systickled;

void  HardFault_Handler(void)
{
	while(1);
}
void	MemManage_Handler(void)
{
	while(1);
}
void	BusFault_Handler(void)
{
	while(1);
}
void	UsageFault_Handler(void)
{
	while(1);
}


__attribute((naked)) void SVC_Handler()
{
	__asm("tst lr,#4 \n\t"
			"ITE EQ \n\t"
			"mrseq r0,MSP\n\t"
			"mrsne r0, PSP \n\t"
			"b OS_SVC_Service");
}


void hw_init()
{
	//by default
	//clock tree (RCC ->SYSTick &cpu ) 8MHZ
	//1 COUnt -> 0.125us
	//x count  -> 1 ms
	//x=8000 count


	//	decrease PenSV  interrupt priority to be  smaller than or equal  SySTICK Timer
	//SysTICK have a priority 14
	__NVIC_SetPriority(PendSV_IRQn, 15) ;

}

void trigger_os_pendsv()
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk ;
}


void Start_Ticker()
{
	//	This clock tree should be defined in HW_init()
	//	8 MHZ
	//	1 count -> 0.125 us
	//	X count -> 1 ms
	//	X = 8000 Count

	 SysTick_Config(8000);

}

void SysTick_Handler()
{
	systickled ^=1;
	MYRTOS_Updata_Waitingtime();
	decide_whatnext();
	trigger_os_pendsv();

}



