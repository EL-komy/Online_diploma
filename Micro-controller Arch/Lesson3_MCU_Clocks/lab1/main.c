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

typedef volatile unsigned int vuint32_t ;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
// register address
#define GPIOA_BASE 0x40010800
#define RCC_BASE   0x40021000

struct bit{
	vuint32_t bit_0:1;
	vuint32_t bit_1:1;
	vuint32_t bit_2:1;
	vuint32_t bit_3:1;
	vuint32_t bit_4:1;
	vuint32_t bit_5:1;
	vuint32_t bit_6:1;
	vuint32_t bit_7:1;
	vuint32_t bit_8:1;
	vuint32_t bit_9:1;
	vuint32_t bit_10:1;
	vuint32_t bit_11:1;
	vuint32_t bit_12:1;
	vuint32_t bit_13:1;
	vuint32_t bit_14:1;
	vuint32_t bit_15:1;
	vuint32_t bit_16:1;
	vuint32_t bit_17:1;
	vuint32_t bit_18:1;
	vuint32_t bit_19:1;
	vuint32_t bit_20:1;
	vuint32_t bit_21:1;
	vuint32_t bit_22:1;
	vuint32_t bit_23:1;
	vuint32_t bit_24:1;

};

union REGS{
	struct bit S_bit;
	vuint32_t ALL;
};
union REGS *GPIOA_CRH   =(union REGS *) (GPIOA_BASE + 0x04);
union REGS *GPIOA_ODR   =(union REGS *) (GPIOA_BASE + 0x0C);
union REGS *RCC_APB2ENR =(union REGS *) (RCC_BASE + 0X18);

int main(void)
{
	RCC_APB2ENR->S_bit.bit_2=1;
	//Init GPIOA
	GPIOA_CRH->S_bit.bit_20=0;
	GPIOA_CRH->S_bit.bit_21=1;
	GPIOA_CRH->S_bit.bit_22=0;
	GPIOA_CRH->S_bit.bit_23=0;
	while(1)
	{
		GPIOA_ODR->S_bit.bit_13=1;
		for (int i = 0; i < 5000; i++); // arbitrary delay
		GPIOA_ODR->S_bit.bit_13=0;
		for (int i = 0; i < 5000; i++); // arbitrary delay
	}
}
