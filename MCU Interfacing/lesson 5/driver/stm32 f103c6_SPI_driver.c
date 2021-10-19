/*
 * stm32 f103c6_SPI_driver.c
 *
 *  Created on: Oct 7, 2021
 *      Author: Mohamed_ELkomy
 */

#include "stm32 f103c6_SPI_driver.h"

/*=================================================================
 *                     Generic Variables
 *=================================================================
 */
SPI_Config_t* G_SPI_Config[2]={NULL,NULL};


/*=================================================================
 *                     Generic Macros
 *=================================================================
 */
#define SPI1_INDEX               0
#define SPI2_INDEX               1

#define SPI_SR_TXE               1<<1
#define SPI_SR_RXNE              1<<0

/*=================================================================
 *                     APIs
 *=================================================================
 */


/**=================================================================
 * @Fn -                    -MCAL_SPI_INIT
 * @brief -                 -INIT SPI Protocol Registers according SPI_Config_t
 * @param [in] -            -SPIx : where x can be (1..2 depending on device used)
 * @param [in] -            -SPI_Config : This is configuration which user will pass it
 * @retval -                -none
 * note -                   -Support for SPI Full Dublex Master/Slave Only & NSS HW/SW
 */
/**================================================================= */

void MCAL_SPI_INIT(SPI_TypeDef_t* SPIx,SPI_Config_t* SPI_Config)
{

	//Safty for registers
	uint16_t TempReg_CR1 = 0;
	uint16_t TempReg_CR2 = 0;

	if(SPIx==SPI1)
	{
		G_SPI_Config[SPI1_INDEX]=SPI_Config;
		RCC_SPI1_CLOCK_EN();
	}
	else if (SPIx==SPI2) {
		G_SPI_Config[SPI2_INDEX]=SPI_Config;
		RCC_SPI2_CLOCK_EN();
	}

	//Set Bit 6 SPE: SPI enable
	TempReg_CR1 |=(1<<6);

	TempReg_CR1 |=SPI_Config->Device_mode;
	TempReg_CR1 |=SPI_Config->comunication_mode;
	TempReg_CR1 |=SPI_Config->frame_format;
	TempReg_CR1 |=SPI_Config->data_size;
	TempReg_CR1 |=SPI_Config->CLK_Polarity;
	TempReg_CR1 |=SPI_Config->CLK_Phase;



	if(SPI_Config->Nss == SPI_NSS_Hard_Master_Output_EN)
	{
		TempReg_CR2 |=SPI_Config->Nss;
	}
	else if (SPI_Config->Nss == SPI_NSS_Hard_Master_Output_DIS) {
		TempReg_CR2 &=SPI_Config->Nss;
	}
	else {
		TempReg_CR1 |=SPI_Config->Nss;
	}

	TempReg_CR1 |=SPI_Config->Bound_rate_pres;

	if(SPI_Config->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		TempReg_CR2 |=SPI_Config->IRQ_Enable;
		if(SPIx==SPI1)
		{
			NVIC_IRQ35_SPI1_ENABLE();
		}
		else if (SPIx==SPI2) {
			NVIC_IRQ36_SPI2_ENABLE();
		}

	}
	SPIx->SPI_CR1=TempReg_CR1;
	SPIx->SPI_CR2=TempReg_CR2;
}

void MCAL_SPI_DeINIT(SPI_TypeDef_t* SPIx)
{
	if(SPIx==SPI1)
	{
		NVIC_IRQ35_SPI1_DISABLE();
		RCC_SPI1_Reset();
	}
	else if (SPIx==SPI2) {
		NVIC_IRQ36_SPI2_DISABLE();
		RCC_SPI2_Reset();
	}
}

void MCAL_SPI_SEND_DATA(SPI_TypeDef_t* SPIx,uint16_t* pTxBuffer,enum PollingMechism PollingEn)
{
	if(PollingEn == PollingEnable)
	{
		while(!((SPIx->SPI_SR) & SPI_SR_TXE));
	}
	SPIx->SPI_DR=*pTxBuffer;
}

void MCAL_SPI_RECEIVE_DATA(SPI_TypeDef_t* SPIx,uint16_t* pTxBuffer,enum PollingMechism PollingEn)
{
	if(PollingEn == PollingEnable)
	{
		while(!((SPIx->SPI_SR) & SPI_SR_RXNE));
	}
	*pTxBuffer=SPIx->SPI_DR;
}

void MCAL_SPI_TX_RX(SPI_TypeDef_t* SPIx,uint16_t* pTxBuffer,enum PollingMechism PollingEn)
{
	if(PollingEn == PollingEnable)
	{
		while(!((SPIx->SPI_SR) & SPI_SR_TXE));
	}
	SPIx->SPI_DR=*pTxBuffer;

	if(PollingEn == PollingEnable)
	{
		while(!((SPIx->SPI_SR) & SPI_SR_RXNE));
	}
	*pTxBuffer=SPIx->SPI_DR;

}

void MCAL_SPI_GPIO_SET_PINS(SPI_TypeDef_t* SPIx)
{

	GPIO_Pinconfig_t Config_pin;

	if(SPIx == SPI1)
	{
		//PA4 : SPI1_NSS
		//PA5 : SPI1_SCK
		//PA6 : SPI1_MISO
		//PA7 : SPI1_MOSI

		if( G_SPI_Config[SPI1_INDEX]->Device_mode ==SPI_Device_Mode_Master )
		{
			switch( G_SPI_Config[SPI1_INDEX]->Nss)
			{
			case SPI_NSS_Hard_Master_Output_EN:
				Config_pin.GPIO_PinNumber = GPIO_PIN_4;
				Config_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				Config_pin.GPIO_Output_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &Config_pin);
				break;
			case SPI_NSS_Hard_Master_Output_DIS:
				Config_pin.GPIO_PinNumber = GPIO_PIN_4;
				Config_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &Config_pin);
				break;
			}

			Config_pin.GPIO_PinNumber = GPIO_PIN_5;
			Config_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			Config_pin.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &Config_pin);

			Config_pin.GPIO_PinNumber = GPIO_PIN_6;
			Config_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &Config_pin);

			Config_pin.GPIO_PinNumber = GPIO_PIN_7;
			Config_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			Config_pin.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &Config_pin);

			//todo to support half duplex and simplex
		}
		else if( G_SPI_Config[SPI1_INDEX]->Device_mode ==SPI_Device_Mode_slave )
		{
			if(G_SPI_Config[SPI1_INDEX]->Nss == SPI_NSS_Hard_slave)
			{
				Config_pin.GPIO_PinNumber = GPIO_PIN_4;
				Config_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &Config_pin);
			}

			Config_pin.GPIO_PinNumber = GPIO_PIN_5;
			Config_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &Config_pin);

			Config_pin.GPIO_PinNumber = GPIO_PIN_6;
			Config_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			Config_pin.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &Config_pin);

			Config_pin.GPIO_PinNumber = GPIO_PIN_7;
			Config_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &Config_pin);
		}
		}

	else if(SPIx == SPI2)
	{
		//PB12 : SPI1_NSS
		//PB13 : SPI1_SCK
		//PB14 : SPI1_MISO
		//PB15 : SPI1_MOSI

		if( G_SPI_Config[SPI2_INDEX]->Device_mode ==SPI_Device_Mode_Master )
		{
			switch( G_SPI_Config[SPI2_INDEX]->Nss)
			{
			case SPI_NSS_Hard_Master_Output_EN:
				Config_pin.GPIO_PinNumber = GPIO_PIN_12;
				Config_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				Config_pin.GPIO_Output_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &Config_pin);
				break;
			case SPI_NSS_Hard_Master_Output_DIS:
				Config_pin.GPIO_PinNumber = GPIO_PIN_12;
				Config_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &Config_pin);
				break;
			}

			Config_pin.GPIO_PinNumber = GPIO_PIN_13;
			Config_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			Config_pin.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &Config_pin);

			Config_pin.GPIO_PinNumber = GPIO_PIN_14;
			Config_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &Config_pin);

			Config_pin.GPIO_PinNumber = GPIO_PIN_15;
			Config_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			Config_pin.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &Config_pin);

			//todo to support half duplex and simplex
		}
	}
	else if( G_SPI_Config[SPI2_INDEX]->Device_mode ==SPI_Device_Mode_slave )
	{
		if(G_SPI_Config[SPI2_INDEX]->Nss == SPI_NSS_Hard_slave)
		{
			Config_pin.GPIO_PinNumber = GPIO_PIN_12;
			Config_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &Config_pin);
		}

		Config_pin.GPIO_PinNumber = GPIO_PIN_13;
		Config_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOB, &Config_pin);

		Config_pin.GPIO_PinNumber = GPIO_PIN_14;
		Config_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		Config_pin.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &Config_pin);

		Config_pin.GPIO_PinNumber = GPIO_PIN_15;
		Config_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOB, &Config_pin);
	}
	//todo to support half duplex and simplex
}


void SPI1_IRQHandler()
{
	struct s_IRQ_SCR irq_s;
	irq_s.TXE =((SPI1->SPI_SR & (1<<1))>>1);
	irq_s.RXNT =((SPI1->SPI_SR & (1<<0))>>0);
	irq_s.ERR =((SPI1->SPI_SR & (1<<4))>>4);
	G_SPI_Config[SPI1_INDEX]->p_IRQ(irq_s);
}

void SPI2_IRQHandler()
{
	struct s_IRQ_SCR irq_s;
	irq_s.TXE =((SPI2->SPI_SR & (1<<1))>>1);
	irq_s.RXNT =((SPI2->SPI_SR & (1<<0))>>0);
	irq_s.ERR =((SPI2->SPI_SR & (1<<4))>>4);
	G_SPI_Config[SPI2_INDEX]->p_IRQ(irq_s);
}
