/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32 f103c6_gpio_driver.h"
#include "stm32 f103c6_EXTI_driver.h"
#include "lcd.h"
#include "keypad.h"

void clock_init()
{
	RCC_GPIOA_CLOCK_EN();
	RCC_GPIOB_CLOCK_EN();
	RCC_AFIO_CLOCK_EN();
}

void EXTI_0()
{
	LCD_clear_screen();

	LCD_WRITE_STRING("EXTERNL_9 INT _| is happened");
	wait(30);
	LCD_clear_screen();
}


int main(void)
{
	EXTI_Pinconfig_t EXT_CONFIG;

	clock_init();
	LCD_INIT();

	EXT_CONFIG.EXTI_PIN = EXTI9PB9;
	EXT_CONFIG.IRQ_EN = EXTI_IRQ_ENABLE;
	EXT_CONFIG.trigger_state = EXTI_TRIGGRE_RISING;
	EXT_CONFIG.P_CallBack = EXTI_0;
	MCAL_EXTI_GPIO_INIT(&EXT_CONFIG);

	LCD_WRITE_STRING("NORMAL STATE");
	wait(30);
	LCD_clear_screen();

	while(1)
	{

	}
}


