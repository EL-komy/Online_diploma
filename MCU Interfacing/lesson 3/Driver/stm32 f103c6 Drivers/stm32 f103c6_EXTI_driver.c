/*
 * stm32 f103c6_gpio_driver.c
 *
 *  Created on: Aug 17, 2021
 *      Author: Mohamed_ELkomy
 */

/*==========================================================*/
//includes
/*==========================================================*/

#include "stm32 f103c6_EXTI_driver.h"


/*==========================================================*/
/* GENARIC VARIABLES */
/*==========================================================*/

//Array Of Pointer To function Tack void and return void
//This Pointer Will Receive The Function From user To Execute when Interrupt in happen

void (* GP_RQL[15])(void);

/*==========================================================*/
/* GENARIC MACROS */
/*==========================================================*/

#define AFIO_EXTI_MAPPING(x)                 ( (x==GPIOA)? 0:\
		                                       (x==GPIOB)? 1:\
				                               (x==GPIOC)? 2:\
						                       (x==GPIOD)? 3:0 )

/*==========================================================*/
/* GENARIC FUNCTIONS  */
/*==========================================================*/

void ENABLE_NVIC(uint8_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_ENABLE();
		break;
	case 1:
		NVIC_IRQ7_EXTI1_ENABLE();
		break;
	case 2:
		NVIC_IRQ8_EXTI2_ENABLE();
		break;
	case 3:
		NVIC_IRQ9_EXTI3_ENABLE();
		break;
	case 4:
		NVIC_IRQ10_EXTI4_ENABLE();
		break;
	case 5 ... 9:
		NVIC_IRQ23_EXTI5_9_ENABLE();
		break;
	case 10 ... 15:
		NVIC_IRQ40_EXTI0_15_ENABLE();
		break;

	}

}
void DISABLE_NVIC(uint8_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_DISABLE();
		break;
	case 1:
		NVIC_IRQ7_EXTI1_DISABLE();
		break;
	case 2:
		NVIC_IRQ8_EXTI2_DISABLE();
		break;
	case 3:
		NVIC_IRQ9_EXTI3_DISABLE();
		break;
	case 4:
		NVIC_IRQ10_EXTI4_DISABLE();
		break;
	case 5 ... 9:
		NVIC_IRQ23_EXTI5_9_DISABLE();
		break;
	case 10 ... 15:
		NVIC_IRQ40_EXTI0_15_DISABLE();
		break;

	}
}

void updata_EXTI(EXTI_Pinconfig_t * EXTI_CONFIG)
{
	//1- Configure GPIO To Be AF input ->Floating Input
	GPIO_Pinconfig_t pin_config;
	pin_config.GPIO_PinNumber = EXTI_CONFIG->EXTI_PIN.EXTI_PIN_num;
	pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_CONFIG->EXTI_PIN.GPIO, &pin_config);

	//2-Update AFIO To Route Between EXTI Line With PORT A,B,C,D
	//This Line Determine The Register For (EXTICR1,EXTICR2,EXTICR3,EXTICR4)

	uint8_t  AFIO_EXTICR_INDEX =  (EXTI_CONFIG->EXTI_PIN.EXTI_LINE_num) /4 ;

	uint8_t  AFIO_EXTI_EXTICR_POSTION =((EXTI_CONFIG->EXTI_PIN.EXTI_LINE_num) %4)*4 ;

	AFIO->EXTICR[AFIO_EXTICR_INDEX] &=~(0XF<<AFIO_EXTI_EXTICR_POSTION);

	AFIO->EXTICR[AFIO_EXTICR_INDEX] |=(AFIO_EXTI_MAPPING(EXTI_CONFIG->EXTI_PIN.GPIO) << AFIO_EXTI_EXTICR_POSTION);

	//3- Update Rising && Falling Edge From (EXTI_FTSR & EXTI_SWIER)
	//First Clear Falling & Rising Edge
	EXTI->RTSR &=~(1<<EXTI_CONFIG->EXTI_PIN.EXTI_LINE_num);
	EXTI->FTSR &=~(1<<EXTI_CONFIG->EXTI_PIN.EXTI_LINE_num);

	if(EXTI_CONFIG->trigger_state == EXTI_TRIGGRE_RISING)
	{
		EXTI->RTSR |=(1<<EXTI_CONFIG->EXTI_PIN.EXTI_LINE_num);
	}
	else if(EXTI_CONFIG->trigger_state == EXTI_TRIGGRE_FALLING)
	{
		EXTI->FTSR |=(1<<EXTI_CONFIG->EXTI_PIN.EXTI_LINE_num);
	}
	else if(EXTI_CONFIG->trigger_state == EXTI_TRIGGRE_RISING_AND_FALLING)
	{
		EXTI->FTSR |=(1<<EXTI_CONFIG->EXTI_PIN.EXTI_LINE_num);
		EXTI->RTSR |=(1<<EXTI_CONFIG->EXTI_PIN.EXTI_LINE_num);
	}
	//4- Update IRQ Handling CallBack*/
	GP_RQL[EXTI_CONFIG->EXTI_PIN.EXTI_LINE_num] = EXTI_CONFIG->P_CallBack;//This Is Address CPU Will jump To Execute Interrupt Handling
	//5-Enable IRQ Interrupt mask register (EXTI_IMR)  AND NVIC
	if(EXTI_CONFIG->IRQ_EN == EXTI_IRQ_ENABLE)
	{
		EXTI->IMR |=(1<< EXTI_CONFIG->EXTI_PIN.EXTI_LINE_num);
		ENABLE_NVIC(EXTI_CONFIG->EXTI_PIN.EXTI_LINE_num);
	}
	else
	{
		EXTI->IMR &=~(1<< EXTI_CONFIG->EXTI_PIN.EXTI_LINE_num);
		DISABLE_NVIC(EXTI_CONFIG->EXTI_PIN.EXTI_LINE_num);
	}


}


/*
 * ========================================================================================
 *                                      FUNCTIONS APIs Definitions
 * ========================================================================================
 *
 */


void MCAL_EXTI_GPIO_INIT(EXTI_Pinconfig_t * EXTI_CONFIG)
{
	updata_EXTI(EXTI_CONFIG);
}


/**=================================================================
 * @Fn -                    -MCAL_EXTI_GPIO_DEINIT
 * @brief -                 -Reset EXTI REGISTERS & NVIC Corresponding IRQ Mask
 * @param [in] -            -none
 * @param [out] -           -none
 * @retval -                -none
 * note -                   -none
 */
/**================================================================= */
void MCAL_EXTI_GPIO_DEINIT(void)
{
	EXTI->IMR=0X0;
	EXTI->EMR=0X0;
	EXTI->RTSR=0X0;
	EXTI->FTSR=0X0;
	EXTI->SWIER=0X0;

	//This bit is set when the selected edge event arrives on the external interrupt line. This bit is
	//cleared by writing a ‘1’ into the bit.

	EXTI->PR=0XFFFFFFFF;

	//Disable EXTI IRQ From NVIC
	NVIC_IRQ6_EXTI0_DISABLE()    ;
	NVIC_IRQ7_EXTI1_DISABLE()    ;
	NVIC_IRQ8_EXTI2_DISABLE()    ;
	NVIC_IRQ9_EXTI3_DISABLE()    ;
	NVIC_IRQ10_EXTI4_DISABLE()   ;
	NVIC_IRQ23_EXTI5_9_DISABLE() ;
	NVIC_IRQ40_EXTI0_15_DISABLE();

}

void MCAL_EXTI_GPIO_UPDATE(EXTI_Pinconfig_t * EXTI_CONFIG)
{
	updata_EXTI(EXTI_CONFIG);

}


/*==========================================================*/
/* ISR FUNCTIONS */
/*==========================================================*/

void EXTI0_IRQHandler()
{
	EXTI->PR |=(1<<0);
	GP_RQL[0]();
}


void EXTI1_IRQHandler(void)
{
	//Clear Binding Register (EXTI_PR) This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR |=(1<<1);
	GP_RQL[1]();

}

void EXTI2_IRQHandler(void)
{
	//Clear Binding Register (EXTI_PR) This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR |=(1<<2);
	GP_RQL[2]();
}

void EXTI3_IRQHandler(void)
{
	//Clear Binding Register (EXTI_PR) This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR |=(1<<3);
	GP_RQL[3]();
}

void EXTI4_IRQHandler(void)
{
	//Clear Binding Register (EXTI_PR) This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR |=(1<<4);
	GP_RQL[4]();
}

void EXTI9_5_IRQHandler(void)
{
	//Clear Binding Register (EXTI_PR) This bit is cleared by writing a ‘1’ into the bit.
	if(EXTI->PR & 1<<5) { EXTI->PR |=(1<<5) ; GP_RQL[5](); }
	if(EXTI->PR & 1<<6) { EXTI->PR |=(1<<6) ; GP_RQL[6](); }
	if(EXTI->PR & 1<<7) { EXTI->PR |=(1<<7) ; GP_RQL[7](); }
	if(EXTI->PR & 1<<8) { EXTI->PR |=(1<<8) ; GP_RQL[8](); }
	if(EXTI->PR & 1<<9) { EXTI->PR |=(1<<9) ; GP_RQL[9](); }

}
void EXTI15_10_IRQHandler(void)
{
	//Clear Binding Register (EXTI_PR) This bit is cleared by writing a ‘1’ into the bit.
	if(EXTI->PR & 1<<10) { EXTI->PR |=(1<<10) ; GP_RQL[10](); }
	if(EXTI->PR & 1<<11) { EXTI->PR |=(1<<11) ; GP_RQL[11](); }
	if(EXTI->PR & 1<<12) { EXTI->PR |=(1<<12) ; GP_RQL[12](); }
	if(EXTI->PR & 1<<13) { EXTI->PR |=(1<<13) ; GP_RQL[13](); }
	if(EXTI->PR & 1<<14) { EXTI->PR |=(1<<14) ; GP_RQL[14](); }
	if(EXTI->PR & 1<<14) { EXTI->PR |=(1<<15) ; GP_RQL[15](); }

}
