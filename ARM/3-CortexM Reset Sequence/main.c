
#include <stdint.h>

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


uint8_t IRQ_Flag = 0;
int cpu_IPSR=1;

enum CpuAaccessLevel{
	privileged,
	unprivileged
};


void switch_access_level(enum CpuAaccessLevel level )
{
	switch (level)
	{
	case privileged:
		__asm("mrs r3,CONTROL \n\t"
				"lsr r3,r3,#0x1 \n\t"
				"lsl r3,r3,#0x1 \n\t"
				"msr CONTROL,r3");
		break;

	case unprivileged:
		__asm("mrs r3,CONTROL \n\t"
				"orr r3,r3,#0x1 \n\t"
				"msr CONTROL,r3");
		break;
	}


}

void EXTI9_CALLBACK(void)
{
	IRQ_Flag = 1;
	switch_access_level(privileged);

}

int main(void)
{
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	//Set EXTI Configuration
	EXTI_PinConfig_t EXTIConfig;
	EXTIConfig.EXTI_PIN = EXTI9PB9;
	EXTIConfig.Trigger_Case = EXTI_Trigger_RISING;
	EXTIConfig.P_IRQ_CallBack = EXTI9_CALLBACK;
	EXTIConfig.IRQ_EN = EXTI_IRQ_Enable;
	MCAL_EXTI_GPIO_Init(&EXTIConfig);



	IRQ_Flag = 1;

	switch_access_level(unprivileged);


	while (1)
	{
		if(IRQ_Flag)
		{
			IRQ_Flag = 0;
		}
		else { /* Misra */ }
	}


}
