/*
 * GPIO.c
 *
 * Created: 22-Aug-21 10:04:58 PM
 *  Author: Mohamed_ELkomy
 */ 
#include "GPIO.h"


/**================================================================
 * @Fn          -MCAL_GPIO_Init
 * @brief       -Initialize the GPIOx PINy according specified parameters in PinConfig
 * @param [in]  -GPIO_x : where x can be (A..D depending on device used)
 * @param [in]  -pin_config pointer to a GPIO_PinConfig_t structure that contains
 * @retval      -none
 * Note         -NONE
 */
void MCAL_GPIO_Init(GPIOX_type_def *GPIOx , GPIO_Pinconfig_t *pin_config)
{
	
	if (pin_config->GPIO_MODE == GPIO_MODE_OUTPUT)
	{
		GPIOx->DDRa |=(pin_config->GPIO_PinNumber);
	}
	else
	{
		if(pin_config->GPIO_MODE == GPIO_MODE_INPUT_PU )
		{
			GPIOx->DDRa &= ~(pin_config->GPIO_PinNumber);
			GPIOx->porta |=(pin_config->GPIO_PinNumber);
		}
		else if(pin_config->GPIO_MODE == GPIO_MODE_INPUT_Hi_Z)
		{
			GPIOx->DDRa &= ~(pin_config->GPIO_PinNumber);
			GPIOx->porta &= ~(pin_config->GPIO_PinNumber);
		}
	}		
}


/**=================================================================
 * @Fn -                    -MCAL_GPIO_Write_pin
 * @brief -                 -Write on specific input pin
 * @param [in] -            -GPIO_x : where x can be (A..D depending on device used)
 * @param [in] -            -pin_num :the number of pin that want to read
 * @param [in] -            -val to write on this bit
 * @retval -                -the input pin value (tow values based on @ref GPIO_PIN_State)
 * note -                   -none
 */
/**================================================================= */

void MCAL_GPIO_Write_pin(GPIOX_type_def *GPIOx ,uint8_t pin_num,uint8_t val)
{
	if(val == GPIO_PIN_SET)
	{
		GPIOx->porta |=(uint8_t) pin_num;
	}
	else
	{
		GPIOx->porta &=~(uint8_t) pin_num;
	}
}


/**=================================================================
 * @Fn -                    -MCAL_GPIO_Write_port
 * @brief -                 -Write on specific port
 * @param [in] -            -GPIO_x : where x can be (A..D depending on device used)
 * @param [in] -            -val to write on this port
 * @retval -                -none
 * note -                   -none
 */
/**================================================================= */

void MCAL_GPIO_Write_port(GPIOX_type_def *GPIOx ,uint8_t val)
{
	GPIOx->porta = val;
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

uint8_t MCAL_GPIO_Read_pin(GPIOX_type_def *GPIOx ,uint8_t pin_num)
{
	uint8_t val;
	val=(GPIOx->PINa)>>pin_num;
}