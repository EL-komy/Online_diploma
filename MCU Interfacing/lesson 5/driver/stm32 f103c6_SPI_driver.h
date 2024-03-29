/*
 * stm32 f103c6_SPI_driver.h
 *
 *  Created on: Oct 7, 2021
 *      Author: Mohamed_ELkomy
 */

#ifndef INC_STM32_F103C6_SPI_DRIVER_H_
#define INC_STM32_F103C6_SPI_DRIVER_H_

/*==========================================================*/
//includes
/*==========================================================*/
#include "stm32f103x6.h"
#include "stm32 f103c6_gpio_driver.h"


//===========================
//Macros Configuration References
//===========================
struct s_IRQ_SCR{
	uint8_t TXE:1;
	uint8_t RXNT:1;
	uint8_t ERR:1;
	uint8_t reserved:5;
};

typedef struct {
	uint16_t Device_mode;               //Specifies the SPI operating mode @Ref SPI_Device_Mode

	uint16_t comunication_mode;         //Specifies the SPI bidirectional mode state @Ref SPI_communication_Mode

	uint16_t frame_format;              //Specifies LSB or MSB @Ref SPI_Frame_Format_Mode

	uint16_t data_size;                 //Specifies Data Size 8Bit or 16Bit @Ref SPI_Data_Size_Mode

	uint16_t CLK_Polarity;              //Specifies CLK_Polarity idle high or idle low @Ref SPI_CLK_Polarity_Mode

	uint16_t CLK_Phase;                 //Specifies CLK_Phase First edge First or Second edge first @Ref SPI_CLK_Phase_Mode

	uint16_t Nss;                      //Specifies NSS is signal managed by SSM bit (SW internal bit (SSI Bit)) or HardWare (NSS pin)  @Ref SPI_NSS_Mode

	uint16_t Bound_rate_pres;           /*Specifies Baud_Rate_Prescaler value which will be used to configure
                                      the Transmit and Receiver SCK Clock. Set This Parameter form @Ref SPI_Baud_Rate_Prescaler
                                      Take care you have to configure RCC to enter the correct clock to APP1 >>to SPI2 or APP2 >>to SPI1 */

	uint16_t IRQ_Enable;             //@Ref SPI_IRQ_Enable

	void(* p_IRQ)(struct s_IRQ_SCR irq_src);  //Set C Function() To call when IRQ happened
                                              //We make the function tack structure to know what means any interrupt


}SPI_Config_t;



//==========================================================
//Macros Configuration References
//==========================================================

/*Ref SPI_Device_Mode*/
#define SPI_Device_Mode_slave                    0
#define SPI_Device_Mode_Master                   (1<<2)    //CR1 .Bit 2 MSTR: Master selection

/*@Ref SPI_communication_Mode*/
#define SPI_commun_1_line_Bidir_Recev_only       (1<<15)           //CR1 .Bit 15 BIDIMODE: Bidirectional data mode enable
#define SPI_commun_1_line_Bidir_Trans_only       (1<<15 |1<<14)  //CR1 .Bit 15 BIDIMODE: Bidirec data enable & Bit 14 BIDIOE: Output enable
#define SPI_commun_2_line                        0
#define SPI_commun_2_line_Recev_only             (1<<10)           //CR1 . Bit 10 RXONLY: Receive only & Bit 15 BIDIMODE: Bidirectional data mode enable

/*@Ref SPI_Frame_Format_Mode*/
#define SPI_Frame_Format_MSB_First               0               //CR1 .Bit 7 LSBFIRST: Frame format 0: MSB transmitted first
#define SPI_Frame_Format_LSB_First               (1<<7)          //CR1. Bit 7 LSBFIRST: Frame format 1: LSB transmitted first

/*@Ref SPI_Data_Size_Mode*/
#define SPI_Data_Size_8_bits                     0             //CR1 Bit 11 DFF: Data frame format 0: 8-bit data frame format
#define SPI_Data_Size_16_bits                    (1<<11)       //CR1 Bit 11 DFF: Data frame format 0: 16-bit data frame format

/*@Ref SPI_CLK_Polarity_Mode*/
#define SPI_CLK_Polarity_low_IDLE                0            //CR1 .Bit1 CPOL: Clock polarity 0: CK to 0 when idle
#define SPI_CLK_Polarity_High_IDLE                (1<<1)       //CR1 .Bit1 CPOL: Clock polarity 1: CK to 1 when idle

/*Ref SPI_CLK_Phase_Mode*/
#define SPI_CLK_Phase_1_Edge__First              0            //CR1. Bit 0 CPHA: Clock phase
#define SPI_CLK_Phase_2_Edge__First              (1<<0)       //CR1. Bit 0 CPHA: Clock phase

/*@Ref SPI_NSS_Mode*/
//HardWare Slave
#define SPI_NSS_Hard_slave                        0        //CR1. Bit 9 SSM: Software slave management 0: Software slave management disabled (means Hardware)
//HardWare Master Output Enable
#define SPI_NSS_Hard_Master_Output_EN            (1<<2)   //CR2. Bit 2 SSOE: SS output enable 1: SS output is enabled in master mode and when the cell is enabled
//HardWare Master Output Disable (Input)
#define SPI_NSS_Hard_Master_Output_DIS           0        //CR2. Bit 2 SSOE: SS Output Disable means it is input to sens if one master take acces on line

//SoftWare
//SoftWare Master
#define SPI_NSS_Soft_Internal_RESET              (1<<9)
#define SPI_NSS_Soft_Internal_SET                (1<<9)|(1<<8)


/*Ref SPI_Baud_Rate_Prescaler*/
//Bits 5:3 BR[2:0]: Baud rate control in CR1
#define SPI_Baud_Rate_Prescaler_2            (0b000<<3)  //000: fPCLK/2
#define SPI_Baud_Rate_Prescaler_4            (0b001<<3)  //001: fPCLK/4
#define SPI_Baud_Rate_Prescaler_8            (0b010<<3)  //010: fPCLK/8
#define SPI_Baud_Rate_Prescaler_16           (0b011<<3)  //011: fPCLK/16
#define SPI_Baud_Rate_Prescaler_32           (0b100<<3)  //100: fPCLK/32
#define SPI_Baud_Rate_Prescaler_64           (0b101<<3)  //101: fPCLK/64
#define SPI_Baud_Rate_Prescaler_128          (0b110<<3)  //110: fPCLK/128
#define SPI_Baud_Rate_Prescaler_256          (0b111<<3)  //111: fPCLK/256

//Ref SPI_IRQ_Enable
#define SPI_IRQ_Enable_NONE                  0

#define SPI_IRQ_Enable_TXEIE_EN              (1<<7) /*CR2 .Bit 7 TXEIE: Tx buffer empty interrupt enable
                                                     1: TXE interrupt not masked. Used to generate an interrupt request when the TXE flag is set.*/

#define SPI_IRQ_Enable_RXNEIE_EN             (1<<6) /*CR2 .Bit 6 RXNEIE: RX buffer not empty interrupt enable
                                                      1: RXNE interrupt not masked. Used to generate an interrupt request when the RXNE flag is set*/

#define SPI_IRQ_Enable_ERRIE_En              (1<<5) //CR2 .Bit 5 ERRIE: Error interrupt enable 1: Error interrupt is enabled



/*
 * ========================================================================================
 *                         APIs Supported by "MCAL GPIO DRIVER"
 * ========================================================================================
 *
 */

enum PollingMechism
{
	PollingEnable,
	PollingDisable
};
void MCAL_SPI_INIT(SPI_TypeDef_t* SPIx,SPI_Config_t* SPI_Config);
void MCAL_SPI_DeINIT(SPI_TypeDef_t* SPIx);
void MCAL_SPI_GPIO_SET_PINS(SPI_TypeDef_t* SPIx);
void MCAL_SPI_SEND_DATA(SPI_TypeDef_t* SPIx,uint16_t* pTxBuffer,enum PollingMechism PollingEn);
void MCAL_SPI_RECEIVE_DATA(SPI_TypeDef_t* SPIx,uint16_t* pTxBuffer,enum PollingMechism PollingEn);
void MCAL_SPI_TX_RX(SPI_TypeDef_t* SPIx,uint16_t* pTxBuffer,enum PollingMechism PollingEn);










#endif /* INC_STM32_F103C6_SPI_DRIVER_H_ */
