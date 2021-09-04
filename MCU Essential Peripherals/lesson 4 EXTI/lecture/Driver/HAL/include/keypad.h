/*
 * keypad.c
 *
 * Created: 8/19/2021 2:21:10 PM
 *  Author: ELKOMY
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stm32 f103c6_gpio_driver.h"

#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4
#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8

GPIO_Pinconfig_t pin_con;

#define KEYPAD_PORT GPIOB
//#define DataDir_KEYPAD_PORT DDRD
//#define keypadPIN PIND

void Keypad_init();
char Keypad_getkey();

#endif /* KEYPAD_H_ */
