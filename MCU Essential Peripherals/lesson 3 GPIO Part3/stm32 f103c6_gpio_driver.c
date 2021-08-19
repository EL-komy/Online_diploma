/*
 * stm32 f103c6_gpio_driver.c
 *
 *  Created on: Aug 17, 2021
 *      Author: Mohamed_ELkomy
 */

#include "stm32 f103c6_gpio_driver.h"

uint8_t GET_Postion(uint16_t pin_num)
{
	switch(pin_num)
	{
	case GPIO_PIN_0:
		return 0;
		break;

	case GPIO_PIN_1:
		return 4;
		break;

	case GPIO_PIN_2:
		return 8;
		break;

	case GPIO_PIN_3:
		return 12;
		break;

	case GPIO_PIN_4:
		return 16;
		break;

	case GPIO_PIN_5:
		return 20;
		break;

	case GPIO_PIN_6:
		return 24;
		break;

	case GPIO_PIN_7:
		return 28;
		break;

	case GPIO_PIN_8:
		return 0;
		break;

	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_11:
		return 12;
		break;

	case GPIO_PIN_12:
		return 16;
		break;

	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_15:
		return 28;
		break;
	default:
		return 0;
		break;

	}
}

/**================================================================
 * @Fn          -MCAL_GPIO_Init
 * @brief       -Initialize the GPIOx PINy according specified parameters in PinConfig
 * @param [in]  -GPIO_x : where x can be (A..E depending on device used)
 * @param [in]  -pin_config pointer to a GPIO_PinConfig_t structure that contains
 * @retval      -none
 * Note         -stmf103c6 MCU has GPIO A,B,C,D,E Modules
 *              but LQFP48 Package has only GPIO A,B, Part of C/D exported external pins
 */
void MCAL_GPIO_Init(GPIO_TypeDef_t *GPIO_x , GPIO_Pinconfig_t *pin_config)
{
	volatile uint32_t *config_register=NULL;
	uint8_t config_pin;
	//To Init Any Pins Must Write On Port configuration register low (GPIOx_CRL) 0>>>7
	//Or register low (GPIOx_CRH) 8>>>15
	//We Determine The Position Should Write On It In  configuration register By Determine First Position Pin

	config_register =(pin_config->GPIO_PinNumber >= GPIO_PIN_8)? &GPIO_x->CRH : &GPIO_x->CRL;

	*(config_register) &=~(0xf << GET_Postion(pin_config->GPIO_PinNumber));
	if (pin_config->GPIO_MODE == GPIO_MODE_OUTPUT_PP || pin_config->GPIO_MODE == GPIO_MODE_OUTPUT_OD ||pin_config->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP || pin_config->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD )
	{
		config_pin=(((pin_config->GPIO_MODE - 4) << 2) | pin_config->GPIO_Output_Speed);
	}
	else
	{
		if(pin_config->GPIO_MODE == GPIO_MODE_Analog || pin_config->GPIO_MODE == GPIO_MODE_INPUT_FLO )
		{
			config_pin=(((pin_config->GPIO_MODE ) << 2));
		}
		else if(pin_config->GPIO_MODE == GPIO_MODE_AF_INPUT)
		{
			config_pin=(((pin_config->GPIO_MODE==GPIO_MODE_INPUT_FLO) << 2));
		}
		else
		{
			config_pin=(((pin_config->GPIO_MODE==GPIO_MODE_INPUT_PU) << 2));

			// 20. Port bit configuration table
			/*In Case GPIO_MODE_INPUT_PU OR GPIO_MODE_INPUT_PD We Put The Same Value 10 In CNF
			And Go To ODR IF GPIO_MODE_INPUT_PU Put 1 And If GPIO_MODE_INPUT_PD Put In ODR 0 Shifting By Bin Number*/

			if(pin_config->GPIO_MODE == GPIO_MODE_INPUT_PU )
			{
				GPIO_x->ODR |=(pin_config->GPIO_PinNumber);
			}
			else
			{
				GPIO_x->ODR &=~(pin_config->GPIO_PinNumber);
			}
		}
	}
	//Write On CRH Or CLH
	*(config_register) |=(config_pin << GET_Postion(pin_config->GPIO_PinNumber));
}

/**=================================================================
 * @Fn -                    -MCAL_GPIO_DeInit
 * @brief -                 -Reset All GPIO Registers
 * @param [in] -            -GPIOx : where x can be (A..E depending on device used)
 * @retval -                -none
 * note -                   -none
 */
/**================================================================= */
void MCAL_GPIO_DeInit(GPIO_TypeDef_t *GPIOx )
{
	/*If MicroController Not Include Reset Controller You Should Make Reset Any Peripheral Manual By Way
		Go To All Registers In This Peripheral And Put On Reset Value*/
	/*GPIOx->CRL  |= 0x44444444;
		GPIOx->CRH  |= 0x44444444;
	    //GPIOx->IDR = (Read Only);
		GPIOx->ODR  |= 0x00000000;
		GPIOx->BRR  |= 0x00000000;
		GPIOx->LCKR |= 0x00000000;
		GPIOx->BSRR |= 0x00000000;*/

	/*If MicroController Include Reset Controller We Reset Any Peripheral By It*/


	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |=(1<<2);
		RCC->APB2RSTR &=~(1<<2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |=(1<<3);
		RCC->APB2RSTR &=~(1<<3);
	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |=(1<<4);
		RCC->APB2RSTR &=~(1<<4);
	}
	else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |=(1<<5);
		RCC->APB2RSTR &=~(1<<5);
	}
	else if(GPIOx == GPIOE)
	{
		RCC->APB2RSTR |=(1<<5);
		RCC->APB2RSTR &=~(1<<5);
	}
}

/**=================================================================
 * @Fn -                    - MCAL_GPIO_Read_pin
 * @brief -                 -Read Specific PIN
 * @param [in] -            -GPIO_x : where x can be (A..E depending on device used)
 * @param [in] -            -pin_num : the number of pin that want to read
 * @retval -                -none
 * note -                   -none
 */
/**================================================================= */

uint8_t MCAL_GPIO_Read_pin(GPIO_TypeDef_t *GPIO_x ,uint16_t pin_num)
{
	uint8_t pin_value;
	if( (GPIO_x->IDR & pin_num) != (uint32_t)GPIO_PIN_RESET )
	{
		pin_value = GPIO_PIN_SET;
	}
	else
	{
		pin_value = GPIO_PIN_RESET;
	}
	return pin_value;
}

/**=================================================================
 * @Fn -                    -MCAL_GPIO_Read_port
 * @brief -                 -Read the input port value
 * @param [in] -            -GPIO_x : where x can be (A..E depending on device used)
 * @retval -                -none
 * note -                   -none
 */
/**================================================================= */

uint16_t MCAL_GPIO_Read_port(GPIO_TypeDef_t *GPIO_x )
{
	uint16_t port;
	port=GPIO_x->IDR;
	return port;
}

/**=================================================================
 * @Fn -                    -MCAL_GPIO_Write_pin
 * @brief -                 -Write on specific input pin
 * @param [in] -            -GPIO_x : where x can be (A..E depending on device used)
 * @param [in] -            -pin_num :the number of pin that want to read
 * @param [in] -            -value to write on this bit
 * @retval -                -the input pin value (tow values based on @ref GPIO_PIN_State)
 * note -                   -none
 */
/**================================================================= */
void MCAL_GPIO_Write_pin(GPIO_TypeDef_t *GPIO_x ,uint16_t pin_num,uint8_t value)
{

	if(value != GPIO_PIN_RESET )
	{
		//GPIO_x->ODR |=(uint32_t) Pin_Number;
		//		Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
		//		These bits are write-only and can be accessed in Word mode only.
		//		0: No action on the corresponding ODRx bit
		//		1: Set the corresponding ODRx bit
		GPIO_x->BSRR =(uint8_t) pin_num;
	}
	else
	{
		//GPIO_x->ODR &=~(uint32_t)(Pin_Number);
		//		Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
		//		These bits are write-only and can be accessed in Word mode only.
		//		0: No action on the corresponding ODRx bit
		//		1: Reset the corresponding ODRx bit
		GPIO_x->BRR=(uint32_t) pin_num;
	}
}

/**=================================================================
 * @Fn -                    -MCAL_GPIO_Write_port
 * @brief -                 -Write on specific port
 * @param [in] -            -GPIO_x : where x can be (A..E depending on device used)
 * @param [in] -            -GPIO_x to write on this port
 * @retval -                -none
 * note -                   -none
 */
/**================================================================= */
void MCAL_GPIO_Write_port(GPIO_TypeDef_t *GPIO_x ,uint16_t value)
{
	GPIO_x->ODR=(uint16_t)value;
}
/**=================================================================
 * @Fn -                    -MCAL_GPIO_Toggle_pin
 * @brief -                 -toggle specific pin
 * @param [in] -            -GPIO_x : where x can be (A..E depending on device used)
 * @param [in] -            -pin_num :the number of pin that want to read
 * @retval -                -none
 * note -                   -none
 */
/**================================================================= */

void MCAL_GPIO_Toggle_pin(GPIO_TypeDef_t *GPIO_x ,uint16_t pin_num)
{
	GPIO_x->ODR ^=pin_num;
}


/**=================================================================
 * @Fn -                    -MCAL_GPIO_Lock_pin
 * @brief -                 -Lock specific pin to be frozen the configuration of this pin
 * @param [in] -            -GPIO_x : where x can be (A..E depending on device used)
 * @param [in] -            -pin_num :the number of pin that want to read
 * @retval -                -Ok if pin config is locked or Error if pin not locked
 *                           (ok & Error are defined @ref GPIO_RETURN_LOCK)
 * note -                   -none
 */
/**================================================================= */
uint8_t MCAL_GPIO_Lock_pin(GPIO_TypeDef_t *GPIO_x ,uint16_t pin_num)
{

	//	This register is used to lock the configuration of the port bits when a correct write sequence
	//	is applied to bit 16 (LCKK). The value of bits [15:0] is used to lock the configuration of the
	//	GPIO. During the write sequence, the value of LCKR[15:0] must not change. When the
	//	LOCK sequence has been applied on a port bit it is no longer possible to modify the value of
	//	the port bit until the next reset.
	//	Each lock bit freezes the corresponding 4 bits of the control register (CRL, CRH).

	GPIO_x->LCKR |=pin_num;

	//	LCKK[16]: Lock key
	//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	//	0: Port configuration lock key not active
	//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	//	LOCK key writing sequence:
	//	Write 1
	//	Write 0
	//	Write 1
	//	Read 0
	//	Read 1 (this read is optional but confirms that the lock is active)
	//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	//	Any error in the lock sequence will abort the lock.
	/*LOCK key writing sequence:*/
	//Write 1
	GPIO_x->LCKR |=(1<<16);
	//Write 0
	GPIO_x->LCKR &=~(1<<16);
	//Write 1
	GPIO_x->LCKR |=(1<<16);
	//Read 0
	if((uint16_t)(GPIO_x->LCKR & 1<<16 ))
	{
		return GPIO_RETURN_LOCK_ENABLED;
	}
	else
	{
		return GPIO_RETURN_LOCK_ERROR;
	}

}


