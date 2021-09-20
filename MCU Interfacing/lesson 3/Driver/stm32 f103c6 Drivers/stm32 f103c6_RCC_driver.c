/*
 * stm32 f103c6_gpio_driver.c
 *
 *  Created on: Aug 17, 2021
 *      Author: Mohamed_ELkomy
 */

/*==========================================================*/
//includes
/*==========================================================*/

#include "stm32 f103c6_RCC_driver.h"

//Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16
const uint8_t APBPrescTable[8u]={0,0,0,0,1,2,3,4};

//Set and cleared by software to control AHB clock division factor.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512
const uint8_t AHBPrescTable[16u]={0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9};

uint32_t MCAL_RCC_GetSYS_CLCKFreq()
{
//	Set and cleared by hardware to indicate which clock source is used as system clock.
//	00: HSI oscillator used as system clock
//	01: HSE oscillator used as system clock
//	10: PLL used as system clock
//	11: Not applicable
	switch((RCC->CFGR >> 2 )& 0b11)
	{
	case 0:
		return HSI_CLK;
		break;
	case 1:
		return HSE_CLK;
		break;
	case 2:
		return 16000000;
		break;
	}
}
uint32_t MCAL_RCC_GetHCLKFreq()
{
	return (MCAL_RCC_GetSYS_CLCKFreq() >>AHBPrescTable[((RCC->CFGR >>4) & 0b1111)]);
}
uint32_t MCAL_RCC_GetPCLK1Freq()
{
	return (MCAL_RCC_GetHCLKFreq() >>APBPrescTable[((RCC->CFGR >>8) & 0b111)]);
}
uint32_t MCAL_RCC_GetPCLK2Freq()
{
	return (MCAL_RCC_GetHCLKFreq() >>APBPrescTable[((RCC->CFGR >>11) & 0b111)]);
}
