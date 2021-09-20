/*
 * stm32 f103c6_USART_driver.H
 *
 *  Created on: Sep 16, 2021
 *      Author: Mohamed_ELkomy
 */

#ifndef INC_STM32_F103C6_USART_DRIVER_H_
#define INC_STM32_F103C6_USART_DRIVER_H_


/*==========================================================*/
//includes
/*==========================================================*/
#include "stm32f103x6.h"
#include "stm32 f103c6_RCC_driver.h"
#include "stm32 f103c6_gpio_driver.h"


#define USART_DIV(PCLK,BaudRate)                (uint32_t)( PCLK/(BaudRate*16) )
#define USART_DIV_MULL_100(PCLK,BaudRate)       (uint32_t)( (25*PCLK/(4*BaudRate)))
#define USART_MANTISSA_MULL_100(PCLK,BaudRate)  (uint32_t)(USART_DIV(PCLK,BaudRate)*100)
#define USART_MANTISSA(PCLK,BaudRate)           (uint32_t)(USART_DIV(PCLK,BaudRate))
#define USART_FRACTION(PCLK,BaudRate)           (uint32_t)(( (USART_DIV_MULL_100(PCLK,BaudRate) - USART_MANTISSA_MULL_100(PCLK,BaudRate)) *16)/100)
#define USART_BRR_REGISTER(PCLK,BaudRate)       ( ((USART_MANTISSA(PCLK,BaudRate))<<4) | (  USART_FRACTION(PCLK,BaudRate)) & 0XF )

enum PoLLing_Mechnism
{
	enable,
	disable
};

typedef struct{
	uint8_t USART_MODE;     //Specifies TX/RX Enable/Disable
                           //This parameter must be set based on @Ref USART_MODE_define

	uint8_t BaudRate;       //Specifies communication Baud Rate
						  //This parameter must be set based on @Ref USART_BaudRate_define

	uint8_t data_len;      //Specifies number of data bits transmitted or received in a frame
						  //This parameter must be set based on @Ref USART_PayLoad_Length_define

	uint8_t parity;        //Specifies the Parity mode
                          //This parameter must be set based on @Ref USART_Parity_define

	uint8_t stop_bits;    //Specifies the StopBits
						//This parameter must be set based on @Ref USART_StopBits_define

	uint8_t HW_Ctrol;    //Specifies the HW_FlowCtrl
    					//This parameter must be set based on @Ref USART_HW_FlowCtrl_define

	uint8_t IRQ_Enable;  //Specifies the IRQ_Enable
						//This parameter must be set based on @Ref USART_IRQ_Enable_define

	void (*p_IRQ_call_back)();  //Set C Function() Which You Need Call it When IRQ is happened

}USART_config;


//===========================
//Macros Configuration References
//===========================

//@Ref USART_MODE_define
#define USART_MODE_TX         (uint32_t)(1<<3)
#define USART_MODE_RX         (uint32_t)(1<<2)
#define USART_MODE_TX_RX      (uint32_t)(1<<3 | 1<<2) //Bit 2 RE: Receiver enable & Bit 3 TE: Transmitter enable

//@Ref USART_BaudRate_define
#define USART_BaudRate_2400            2400
#define USART_BaudRate_9600            9600
#define USART_BaudRate_19200           19200
#define USART_BaudRate_57600           57600
#define USART_BaudRate_115200          115200
#define USART_BaudRate_230400          230400
#define USART_BaudRate_460800          460800
#define USART_BaudRate_921600          921600
#define USART_BaudRate_2250000         2250000
#define USART_BaudRate_4500000         4500000

// @Ref USART_PayLoad_Length_define

#define  USART_data_Length_8B    0
#define  USART_data_Length_9B    (uint32_t)(1<<12)

// @Ref USART_Parity_define

#define USART_Parity_NONE        0
#define USART_Parity_Odd         (uint32_t)(1<<9 | 1<<10)
#define USART_Parity_Even        (uint32_t)(1<<10)

//@Ref USART_StopBits_define
#define USART_StopBits_1         0
#define USART_StopBits_Hafe      (uint32_t)(1<<12)
#define USART_StopBits_2         (uint32_t)(1<<13)
#define USART_StopBits_1_Hafe    (uint32_t)(1<<12 | 1<<13)


//@Ref USART_HW_FlowCtrl_define

#define USART_HW_FlowCtrl_NONE        0
#define USART_HW_FlowCtrl_CTS        (uint32_t)(1<<9)
#define USART_HW_FlowCtrl_RTS        (uint32_t)(1<<8)
#define USART_HW_FlowCtrl_CTS_RTS    (uint32_t)(1<<9 | 1<<8)

//@Ref USART_IRQ_Enable_define

#define USART_IRQ_Enable_NONE         0
#define USART_IRQ_Enable_TXE		  (uint32_t)(1<<7)
#define USART_IRQ_Enable_TC			  (uint32_t)(1<<6)
#define USART_IRQ_Enable_RXNE         (uint32_t)(1<<5)
#define USART_IRQ_Enable_PE           (uint32_t)(1<<8)



/*
 * ========================================================================================
 *                         APIs Supported by "MCAL USART DRIVER"
 * ========================================================================================
 *
 */

void MCAL_UART_INIT(USART_TypeDef_t* USARTx,USART_config * UART_Config);
void MCAL_UART_DeINIT(USART_TypeDef_t* USARTx,USART_config * UART_Config);
void MCAL_UART_GPIO_Set_Pins(USART_TypeDef_t* USARTx);
void MCAL_UART_SEND_DATA(USART_TypeDef_t* USARTx,uint16_t* pTXBuffer,enum PoLLing_Mechnism PollengEn);
void MCAL_UART_RECEIVE_DATA(USART_TypeDef_t* USARTx,uint16_t* pTXBuffer,enum PoLLing_Mechnism PollengEn);
void MCAL_UART_WAIT_TC(USART_TypeDef_t* USARTx);


#endif /* INC_STM32_F103C6_USART_DRIVER_H_ */
