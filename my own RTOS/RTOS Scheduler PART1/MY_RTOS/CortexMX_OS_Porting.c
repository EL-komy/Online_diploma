/*
 * CortexMX_OS_Porting.c
 *
 *  Created on: Apr 29, 2024
 *      Author: Elkomy
 */



#include "CortexMX_OS_Porting.h"


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
  }
