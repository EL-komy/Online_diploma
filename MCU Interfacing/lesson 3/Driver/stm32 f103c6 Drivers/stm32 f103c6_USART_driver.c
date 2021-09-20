/*
 * stm32 f103c6_USART_driver.c
 *
 *  Created on: Sep 18, 2021
 *      Author: Mohamed_ELkomy
 */

#include "stm32 f103c6_USART_driver.h"


/*==========================================================*/
/*Generic Variables*/
/*==========================================================*/


USART_config* Global_UART_Config = NULL;


/* ==============================================================
 *              APIs Supported by "MCAL USART DRIVER"
 * ===============================================================*/


/*=================================================================
 * @Fn -                    -MCAL_UART_INIT
 * @brief -                 -Initialize the USARTx according specified parameters in USART_Config
 * @param [in] -            -USARTx : where x can be (1,2,3 depending on device used)
 * @param [in] -            -UART_Config pointer to a UART_Config structure that contains
 * @retval -                -none
 * note -                   -none
 *
================================================================= */

void MCAL_UART_INIT(USART_TypeDef_t* USARTx,USART_config * UART_Config)
{
	uint32_t pclk ,BRR;
	Global_UART_Config = UART_Config;

	//Enable Clock For Given USART Peripheral
	if(USARTx == USART1)
	{
		RCC_USART1_CLOCK_EN();
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_CLOCK_EN();
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_CLOCK_EN();
	}

	//Enable UART Module Bit 13 UE: USART enable
	USARTx->CR1 |=(1<<13);

	//Enable TX RX according to the USART_MODE configuration item
	USARTx->CR1 |=UART_Config->USART_MODE;

	//DATA Length
	USARTx->CR1 |=UART_Config->data_len;

	//Baud Rate
	USARTx->CR1 |=UART_Config->BaudRate;

	//Parity
	USARTx->CR1 |=UART_Config->parity;

	//StopBits
	USARTx->CR1 |=UART_Config->stop_bits;

	//HW_FlowCtrl
	USARTx->CR1 |=UART_Config->HW_Ctrol;

	//IRQ_Enable
	USARTx->CR1 |=UART_Config->IRQ_Enable;

	//Configuration of BRR(BaudRate Register)
	if(USARTx == USART1)
	{
		pclk=MCAL_RCC_GetPCLK2Freq();
	}
	else
	{
		pclk=MCAL_RCC_GetPCLK1Freq();
	}
	BRR=USART_BRR_REGISTER(pclk,UART_Config->BaudRate);
	USARTx->BRR=BRR;

	//IRQ_Enable
	if(UART_Config->IRQ_Enable != USART_IRQ_Enable_NONE )
	{
		USARTx->CR1 |=UART_Config->IRQ_Enable;

		if(USARTx == USART1)
		{
			NVIC_IRQ37_USART1_ENABLE();
		}
		else if(USARTx == USART2)
		{
			NVIC_IRQ38_USART2_ENABLE();
		}
		else if(USARTx == USART3)
		{
			NVIC_IRQ39_USART3_ENABLE();
		}

	}
}


/*=================================================================
 * @Fn -                    -MCAL_UART_DeINIT
 * @brief -                 -Reset All USART Registers
 * @param [in] -            -USARTx : where x can be (1,2,3)
 * @retval -                -none
 * note -                   -none
================================================================= */
void MCAL_UART_DeINIT(USART_TypeDef_t* USARTx,USART_config * UART_Config)
{
	if(USARTx == USART1)
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_DISABLE();
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_Reset();
		NVIC_IRQ38_USART2_DISABLE();
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_Reset();
		NVIC_IRQ39_USART3_DISABLE();
	}
}


/**================================================================
 * @Fn 				-	MCAL_UART_GPIO_Set_Pins
 * @brief 			-	Initializes GPIO Pins to be connected with the selected UART
 * @param [in] 		- 	USARTx : where x can be (1..3 depending on device used) to select USART peripheral
 * @retval 			-	none
 * Note 			-	Must open clock for AFIO & GPIO After GPIO Initialization
 *
 */
void MCAL_UART_GPIO_Set_Pins(USART_TypeDef_t* USARTx)
{
	GPIO_Pinconfig_t pin_confg;
	if(USARTx == USART1)
	{
		/* PA9  ->TX
		 * PA10 ->RX
		 * PA11 ->CTS
		 * PA12 ->RTS
		 */

		//TX pin at PA9
		pin_confg.GPIO_PinNumber=GPIO_PIN_9;
		pin_confg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
		pin_confg.GPIO_Output_Speed=GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA,&pin_confg);

		//RX pin at PA10
		pin_confg.GPIO_PinNumber=GPIO_PIN_10;
		pin_confg.GPIO_MODE=GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOA,&pin_confg);

		//Check for Flow Control when Enabled
		if(Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS || Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS_RTS)
		{
			//CTS at Pin PA11
			pin_confg.GPIO_PinNumber=GPIO_PIN_11;
			pin_confg.GPIO_MODE=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA,&pin_confg);
		}
		if(Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_RTS || Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS_RTS)
		{
			//RTS at Pin PA12
			pin_confg.GPIO_PinNumber=GPIO_PIN_12;
			pin_confg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
			pin_confg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA,&pin_confg);
		}
	}

	if(USARTx == USART2)
	{
		/* PA2  ->TX
		 * PA3 ->RX
		 * PA0 ->CTS
		 * PA1 ->RTS
		 */

		pin_confg.GPIO_PinNumber=GPIO_PIN_2;
		pin_confg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
		pin_confg.GPIO_Output_Speed=GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA,&pin_confg);

		pin_confg.GPIO_PinNumber=GPIO_PIN_3;
		pin_confg.GPIO_MODE=GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOA,&pin_confg);

		//Check for Flow Control when Enabled
		if(Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS || Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS_RTS)
		{

			pin_confg.GPIO_PinNumber=GPIO_PIN_0;
			pin_confg.GPIO_MODE=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA,&pin_confg);
		}
		if(Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_RTS || Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS_RTS)
		{
			//RTS at Pin PA12
			pin_confg.GPIO_PinNumber=GPIO_PIN_1;
			pin_confg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
			pin_confg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA,&pin_confg);
		}
	}

	if(USARTx == USART2)
	{

		/* PB10 ->TX
		 * PB11 ->RX
		 * PB13 ->CTS
		 * PB14 ->RTS
		 */

		pin_confg.GPIO_PinNumber=GPIO_PIN_10;
		pin_confg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
		pin_confg.GPIO_Output_Speed=GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB,&pin_confg);

		pin_confg.GPIO_PinNumber=GPIO_PIN_11;
		pin_confg.GPIO_MODE=GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOB,&pin_confg);

		//Check for Flow Control when Enabled
		if(Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS || Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS_RTS)
		{

			pin_confg.GPIO_PinNumber=GPIO_PIN_13;
			pin_confg.GPIO_MODE=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB,&pin_confg);
		}
		if(Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_RTS || Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS_RTS)
		{
			//RTS at Pin PA12
			pin_confg.GPIO_PinNumber=GPIO_PIN_14;
			pin_confg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
			pin_confg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB,&pin_confg);
		}
	}
}

/**================================================================
 * @Fn 				-	MCAL_UART_SendData
 * @brief 			-	Send Buffer With UART
 * @param [in] 		- 	USARTx : where x can be (1..3 depending on device used) to select USART peripheral
 * @param [in] 		- 	TxBuffer : Buffer Which holds the TX data
 * @param [in] 		- 	PollingEN : Enable Polling or Disable it
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_UART_SEND_DATA(USART_TypeDef_t* USARTx,uint16_t* pTXBuffer,enum PoLLing_Mechnism PollengEn)
{
	if(PollengEn == enable)
	{
		//Wait until TXE flag is set in SR
		while(!(USARTx->SR &(1<<7)));
	}

	//check the USART_PayLoad_Length (9B or 8B)

	/*When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	because it is replaced by the parity.
	When receiving with the parity enabled, the value read in the MSB bit is the received parity
	bit.*/
	if(Global_UART_Config->data_len == USART_data_Length_9B)
	{
		USARTx->DR= (*pTXBuffer & (uint16_t)0x01ff);
	}
	if(Global_UART_Config->data_len == USART_data_Length_8B)
	{
		USARTx->DR= (*pTXBuffer & (uint8_t)0xff);
	}
}

/**================================================================
 * @Fn 				-	MCAL_UART_ReceiveData
 * @brief 			-	Receive Buffer With UART
 * @param [in] 		- 	USARTx : where x can be (1..3 depending on device used) to select USART peripheral
 * @param [in] 		- 	RxBuffer : Buffer which holds Received data
 * @param [in] 		- 	PollingEN : Enable Polling or Disable it
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_UART_RECEIVE_DATA(USART_TypeDef_t* USARTx,uint16_t* pTXBuffer,enum PoLLing_Mechnism PollengEn)
{
	if(PollengEn == enable)
	{
		//wait till RXNE flag is set in the SR
		while(!(USARTx->SR &(1<<5)));
	}
	if(Global_UART_Config->data_len == USART_data_Length_9B)
	{
		if(Global_UART_Config->parity == USART_Parity_NONE)
		{
			(*(uint16_t*) pTXBuffer)=USARTx->DR;
		}
		else
		{
			(*(uint16_t*) pTXBuffer)=(USARTx->DR & (uint8_t)0xff);
		}
	}
	if(Global_UART_Config->data_len == USART_data_Length_8B)
	{
		if(Global_UART_Config->parity == USART_Parity_NONE)
		{
			(*(uint16_t*) pTXBuffer)=(USARTx->DR & (uint8_t)0xff);
		}
		else
		{
			(*(uint16_t*) pTXBuffer)=(USARTx->DR & (uint8_t)0x7f);
		}
	}
}


/**================================================================
 * @Fn 				-	MCAL_UART_WAIT_TC
 * @brief 			-	Waits for transmission complete flag for last data transmitted
 * @param [in] 		- 	USARTx : where x can be (1..3 depending on device used) to select USART peripheral
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_UART_WAIT_TC(USART_TypeDef_t* USARTx)
{
	//wait till TC flag is set in the SR
	while(!(USARTx->SR & (1<<6)));
}


//ISR
void USART1_IRQHandler()
{
	Global_UART_Config->p_IRQ_call_back();
}

void USART2_IRQHandler()
{
	Global_UART_Config->p_IRQ_call_back();
}

void USART3_IRQHandler()
{
	Global_UART_Config->p_IRQ_call_back();
}
