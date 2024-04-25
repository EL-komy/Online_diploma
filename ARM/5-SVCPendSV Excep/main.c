

#include <stdint.h>
#include "core_cm3.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "STM32F103x8.h"
#include "stm32f103x8_gpio_driver.h"
#include "lcd.h"
#include "keypad.h"
#include "stm32f103x8_EXTI_driver.h"
#include "stm32f103x8_USART_driver.h"
#include "stm32f103x8_SPI_driver.h"
#include "stm32f103x8_I2C_driver.h"
#include "I2C_Slave_EEPROM.h"


uint8_t TaskA_Flag,TaskB_Flag, IRQ_Flag = 0;
int result , cpu_IPSR=1;

extern int _estack;

#define TaskA_Stack_Size 100
#define TaskB_Stack_Size 100

#define OS_SET_PSP(add)              __asm volatile("mov r0,%0 \n\t msr PSP,r0" : :"r" (add))

#define OS_SWITCH_SP_TO_PSP         __asm volatile("mrs r0,CONTROL \n\t mov r1,#0x02 \n\t orr r0,r0,r1 \n\t msr CONTROL,r0")
#define OS_SWITCH_SP_TO_MSP         __asm volatile("mrs r0,CONTROL \n\t mov r1,#0x05 \n\t and r0,r0,r1 \n\t msr CONTROL,r0")

#define OS_SWITCH_ACCESS_TO_UNPRI    __asm("mrs r3,CONTROL \n\t orr r3,r3,#0x1 \n\t msr CONTROL,r3")

#define OS_SWITCH_ACCESS_TO_PRI      __asm("mrs r3,CONTROL \n\t lsr r3,r3,#0x1 \n\t lsl r3,r3,#0x1\n\t msr CONTROL,r3")

#define OS_Generate_Exception        __asm("SVC #0X3")


unsigned int _S_MSP=  &_estack;
unsigned int _E_MSP;

unsigned int _S_PSP_TA;
unsigned int _E_PSP_TA;

unsigned int _S_PSP_TB;
unsigned int _E_PSP_TB;


void EXTI9_CALLBACK(void)
{
	if(IRQ_Flag==0)
	{
		TaskA_Flag=1;
		IRQ_Flag=1;
	}
	else if(IRQ_Flag==1)
	{
		TaskB_Flag=1;
		IRQ_Flag=0;
	}
}


int TaskA(int a,int b,int c)
{
	return (a+b+c);
}

int TaskB(int a,int b,int c,int d)
{
	return (a+b+c+d);
}


void main_os()
{
	_E_MSP=(_S_MSP -512);

	_S_PSP_TA=(_E_MSP-8);
	_E_PSP_TA=(_S_PSP_TA-TaskA_Stack_Size);

	_S_PSP_TB=(_E_PSP_TA-8);
	_E_PSP_TB=(_S_PSP_TB-TaskB_Stack_Size);

	while(1)
	{
		__asm("nop");
		if(TaskA_Flag==1)
		{
			//set psp = s_psp_ta
			OS_SET_PSP(_S_PSP_TA);
			// sp -> psp
			OS_SWITCH_SP_TO_PSP;
			//switch privileged 2 unprivileged
			OS_SWITCH_ACCESS_TO_UNPRI;

			result=TaskA(1, 2, 3);

			//switch unprivileged 2 privileged
			OS_Generate_Exception;
			// sp -> msp
			OS_SWITCH_SP_TO_MSP;
			TaskA_Flag=0;

		}
		else if(TaskB_Flag==1)
		{
			//set psp = s_psp_tb
			OS_SET_PSP(_S_PSP_TB);
			// sp -> psp
			OS_SWITCH_SP_TO_PSP;
			//switch privileged 2 unprivileged
			OS_SWITCH_ACCESS_TO_UNPRI;

			result=TaskB(1, 2, 3,4);

			//switch unprivileged 2 privileged
			OS_Generate_Exception;
			// sp -> msp
			OS_SWITCH_SP_TO_MSP;
			TaskB_Flag=0;
		}

	}

}


void OS_SVC_Service(int * StackFramePointer)
{
	unsigned char SVC_num;
	unsigned int v1,v2;
	SVC_num=    *((unsigned char*)(((unsigned char*)StackFramePointer[6])-2));
	v1=StackFramePointer[0];
	v2=StackFramePointer[1];

	switch(SVC_num)
	{
		case 1:
			StackFramePointer[0]=v1+v2;
			break;
		case 2:
			StackFramePointer[0]=v1-v2;
				break;
		case 3:
			StackFramePointer[0]=v1*v2;
				break;
		case 4:
			SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

					break;
	}


}
__attribute((naked)) void SVC_Handler()
{
	__asm("tst lr,#4 \n\t"
			"ITE EQ \n\t"
			"mrseq r0,MSP\n\t"
			"mrsne r0, PSP \n\t"
			"b OS_SVC_Service");
}


int OS_SVC_Set(int a,int b,int SVC_ID)
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

	__asm("mov %0,r0"
			: "=r" (res));

	return res;
}

void PendSV_Handler()
{
	__asm("nop");
}


int main(void)
{
//	RCC_GPIOB_CLK_EN();
//	RCC_AFIO_CLK_EN();
//
//	//Set EXTI Configuration
//	EXTI_PinConfig_t EXTIConfig;
//	EXTIConfig.EXTI_PIN = EXTI9PB9;
//	EXTIConfig.Trigger_Case = EXTI_Trigger_RISING;
//	EXTIConfig.P_IRQ_CallBack = EXTI9_CALLBACK;
//	EXTIConfig.IRQ_EN = EXTI_IRQ_Enable;
//	MCAL_EXTI_GPIO_Init(&EXTIConfig);
//
//	main_os();

	IRQ_Flag = 1;
	IRQ_Flag=OS_SVC_Set(3,3,1);
	IRQ_Flag=OS_SVC_Set(3,3,2);
	IRQ_Flag=OS_SVC_Set(3,3,3);
	OS_SVC_Set(10,2,4);





	while (1)
	{
		if(IRQ_Flag)
		{
			IRQ_Flag = 0;
		}
		else { /* Misra */ }
	}


}
