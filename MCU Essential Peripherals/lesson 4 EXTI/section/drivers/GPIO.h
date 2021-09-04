/*
 * GPIO.h
 *
 * Created: 22-Aug-21 6:12:57 PM
 *  Author: Mohamed_ELkomy
 */ 


#ifndef GPIO_H_
#define GPIO_H_


//-----------------------------
//Includes
//-----------------------------
#include"stdlib.h"
#include"stdint.h"

//-----------------------------
//Base addresses for BUS Peripherals
//-----------------------------

#define PORTA_BASE     0x39UL
#define PORTB_BASE     0x36UL
#define PORTC_BASE     0x33UL
#define PORTD_BASE     0x30UL

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{
	uint8_t PINa ;
	uint8_t DDRa ;
	uint8_t porta ;
	}GPIOX_type_def;
	
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA                   ((GPIOX_type_def *)PORTA_BASE)
#define GPIOB                   ((GPIOX_type_def *)PORTB_BASE)
#define GPIOC                   ((GPIOX_type_def *)PORTC_BASE)
#define GPIOD                   ((GPIOX_type_def *)PORTD_BASE)


//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct{
	uint8_t GPIO_PinNumber;     //specifies the GPIO pins to configured
							     //this parameter can be a value of @ref GPIO_PINS_def

	uint8_t GPIO_MODE;          //specifies THE operating  mode for selected pin
	                            //this parameter can be a value of @ref GPIO_MODE_def

}GPIO_Pinconfig_t;

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref GPIO_PINS_def

#define GPIO_PIN_0               ((uint8_t )0x01)  //Pin 0 Selected
#define GPIO_PIN_1               ((uint8_t )0x02)  //Pin 1 Selected
#define GPIO_PIN_2               ((uint8_t )0x04)  //Pin 2 Selected
#define GPIO_PIN_3               ((uint8_t )0x08)  //Pin 3 Selected
#define GPIO_PIN_4               ((uint8_t )0x10)  //Pin 4 Selected
#define GPIO_PIN_5               ((uint8_t )0x20)  //Pin 5 Selected
#define GPIO_PIN_6               ((uint8_t )0x40)  //Pin 6 Selected
#define GPIO_PIN_7               ((uint8_t )0x80)  //Pin 7 Selected

//@ref GPIO_MODE_define

#define GPIO_MODE_INPUT_PU         0x00000000u  //Input with pull-up
#define GPIO_MODE_INPUT_Hi_Z         0x00000001u  //pull-down
#define GPIO_MODE_OUTPUT           0x00000002u  //General purpose output push-pull


//@ref GPIO_PIN_State
#define GPIO_PIN_SET                 1
#define GPIO_PIN_RESET               0


/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void MCAL_GPIO_Init(GPIOX_type_def *GPIOx , GPIO_Pinconfig_t *pin_config);
uint8_t MCAL_GPIO_Read_pin(GPIOX_type_def *GPIOx ,uint8_t pin_num);
uint8_t MCAL_GPIO_Read_port(GPIOX_type_def *GPIOx );
void MCAL_GPIO_Write_pin(GPIOX_type_def *GPIOx ,uint8_t pin_num,uint8_t val);
void MCAL_GPIO_Write_port(GPIOX_type_def *GPIOx ,uint8_t val);


#endif /* GPIO_H_ */