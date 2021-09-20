/*
 * stm32 f103c6_RCC_driver.H
 *
 *  Created on: Sep 16, 2021
 *      Author: Mohamed_ELkomy
 */

#ifndef INC_STM32_F103C6_RCC_DRIVER_H_
#define INC_STM32_F103C6_RCC_DRIVER_H_

#include "stm32f103x6.h"

#define HSI_CLK      (uint32_t)8000000
#define HSE_CLK      (uint32_t)16000000
uint32_t MCAL_RCC_GetSYS_CLCKFreq();
uint32_t MCAL_RCC_GetHCLKFreq();
uint32_t MCAL_RCC_GetPCLK1Freq();
uint32_t MCAL_RCC_GetPCLK2Freq();

#endif /* INC_STM32_F103C6_RCC_DRIVER_H_ */
