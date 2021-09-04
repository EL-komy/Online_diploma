/*
 * LCD.c
 *
 * Created: 8/19/2021 2:21:10 PM
 *  Author: ELKOMY
 */

#include "lcd.h"


void wait(uint32_t time)
{
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}

void LCD_clear_screen(){
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void LCD_lcd_kick(){
	MCAL_GPIO_Write_pin(LCD_CTRL, EN_SWITCH, GPIO_PIN_SET);
//	LCD_CTRL |= (1 << EN_SWITCH);
	wait(100);
	MCAL_GPIO_Write_pin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
//	LCD_CTRL &= ~(1 << EN_SWITCH);
}

void LCD_GOTO_XY(unsigned char line, unsigned char position){
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}

void LCD_INIT(){
	wait(90);
	
	
	pin_con.GPIO_PinNumber=RS_SWITCH;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pin_con);

	pin_con.GPIO_PinNumber=RW_SWITCH;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pin_con);

	pin_con.GPIO_PinNumber=EN_SWITCH;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pin_con);
	//===============================
	
	#ifdef EIGHT_BIT_MODE
	

	pin_con.GPIO_PinNumber=GPIO_PIN_0;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &pin_con);

	pin_con.GPIO_PinNumber=GPIO_PIN_1;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &pin_con);

	pin_con.GPIO_PinNumber=GPIO_PIN_2;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &pin_con);

	pin_con.GPIO_PinNumber=GPIO_PIN_3;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &pin_con);

	pin_con.GPIO_PinNumber=GPIO_PIN_4;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &pin_con);

	pin_con.GPIO_PinNumber=GPIO_PIN_5;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &pin_con);

	pin_con.GPIO_PinNumber=GPIO_PIN_6;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &pin_con);

	pin_con.GPIO_PinNumber=GPIO_PIN_7;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &pin_con);

//	DataDir_LCD_CTRL |= (1<<EN_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
	MCAL_GPIO_Write_pin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_Write_pin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_Write_pin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);

//	LCD_CTRL &= ~ (1<<EN_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
//	DataDir_LCD_PORT = 0xFF;
	wait(15);
	LCD_clear_screen();
	
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);

	#endif
	#ifdef FOUR_BIT_MODE
	
	
	pin_con.GPIO_PinNumber=GPIO_PIN_4;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &pin_con);

	pin_con.GPIO_PinNumber=GPIO_PIN_5;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &pin_con);

	pin_con.GPIO_PinNumber=GPIO_PIN_6;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &pin_con);

	pin_con.GPIO_PinNumber=GPIO_PIN_7;
	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &pin_con);
	
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
	#endif

}

void LCD_check_lcd_isbusy()
{
	//	DataDir_LCD_PORT &= ~(0xFF<<DATA_shift);
	LCD_PORT->DDRa=0x00;

// 	pin_con.GPIO_PinNumber=GPIO_PIN_0;
// 	pin_con.GPIO_MODE=GPIO_MODE_INPUT_PU;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_1;
// 	pin_con.GPIO_MODE=GPIO_MODE_INPUT_PU;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_2;
// 	pin_con.GPIO_MODE=GPIO_MODE_INPUT_PU;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_3;
// 	pin_con.GPIO_MODE=GPIO_MODE_INPUT_PU;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_4;
// 	pin_con.GPIO_MODE=GPIO_MODE_INPUT_PU;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_5;
// 	pin_con.GPIO_MODE=GPIO_MODE_INPUT_PU;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_6;
// 	pin_con.GPIO_MODE=GPIO_MODE_INPUT_PU;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_7;
// 	pin_con.GPIO_MODE=GPIO_MODE_INPUT_PU;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);

//	LCD_CTRL |= (1 << RW_SWITCH);
//	LCD_CTRL &= ~(1 << RS_SWITCH);
	MCAL_GPIO_Write_pin(LCD_CTRL, RW_SWITCH, GPIO_PIN_SET);
	MCAL_GPIO_Write_pin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);

	LCD_lcd_kick();
	while(MCAL_GPIO_Read_pin(LCD_PORT,GPIO_PIN_6)==1)
	{
		LCD_lcd_kick();
	}
	LCD_lcd_kick();
//	DataDir_LCD_PORT |= (0xFF<<DATA_shift);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_0;
// 	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
// 	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_1;
// 	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
// 	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_2;
// 	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
// 	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_3;
// 	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
// 	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_4;
// 	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
// 	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_5;
// 	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
// 	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_6;
// 	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
// 	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);
// 
// 	pin_con.GPIO_PinNumber=GPIO_PIN_7;
// 	pin_con.GPIO_MODE=	GPIO_MODE_OUTPUT;
// 	//pin_con.GPIO_Output_Speed=GPIO_SPEED_10M;
// 	MCAL_GPIO_Init(LCD_PORT, &pin_con);

	
//	LCD_CTRL &= ~(1 << RW_SWITCH);
	MCAL_GPIO_Write_pin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	
	LCD_PORT->DDRa=0xff;

}


void LCD_WRITE_COMMAND(unsigned char command){
	#ifdef EIGHT_BIT_MODE
		LCD_check_lcd_isbusy();
//		LCD_PORT = command;
		MCAL_GPIO_Write_port(LCD_PORT, command);
//		LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
		MCAL_GPIO_Write_pin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
		MCAL_GPIO_Write_pin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
		wait(1);
		LCD_lcd_kick();
	#endif
	#ifdef FOUR_BIT_MODE
		LCD_check_lcd_isbusy();
		/*LCD_PORT->porta = (LCD_PORT->porta  & 0x0F) | (command & 0xF0);*/
		MCAL_GPIO_Write_port(LCD_PORT,command>>4);
		//LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
		MCAL_GPIO_Write_pin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
		MCAL_GPIO_Write_pin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
		LCD_lcd_kick ();
		/*LCD_PORT->porta  = (LCD_PORT->porta  & 0x0F) | (command << 4);*/
		MCAL_GPIO_Write_port(LCD_PORT,(command<<4));
		//LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
		MCAL_GPIO_Write_pin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
		MCAL_GPIO_Write_pin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
		LCD_lcd_kick();
	#endif
}

void LCD_WRITE_CHAR( unsigned char character){
	#ifdef EIGHT_BIT_MODE
		LCD_check_lcd_isbusy();
//		LCD_PORT = character;
		MCAL_GPIO_Write_port(LCD_PORT, character>>4);
//		LCD_CTRL &= ~(1 << RW_SWITCH);
//		LCD_CTRL |= (1 << RS_SWITCH);
		MCAL_GPIO_Write_pin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);
		MCAL_GPIO_Write_pin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
		wait(10);
		LCD_lcd_kick();
	#endif
	#ifdef FOUR_BIT_MODE
		LCD_check_lcd_isbusy();
		MCAL_GPIO_Write_port(LCD_PORT,character);
		//LCD_PORT->porta = (LCD_PORT->porta & 0x0F) | (character & 0xF0);
		//LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
		//LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
		MCAL_GPIO_Write_pin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);
		MCAL_GPIO_Write_pin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
		wait(100);
		LCD_lcd_kick();
		
		MCAL_GPIO_Write_port(LCD_PORT,(character<<4));
		/*LCD_PORT->porta = (LCD_PORT->porta & 0x0F) | (character << 4);*/
		//LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
		//LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
		MCAL_GPIO_Write_pin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);
		MCAL_GPIO_Write_pin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
		wait(100);
		LCD_lcd_kick ();
	#endif
}

void LCD_WRITE_STRING(char* string){
	int count = 0;
	while (*string > 0){
		count++;
		LCD_WRITE_CHAR(*string++);
		if (count == 16)
		{
			LCD_GOTO_XY(2,0);
		}
		else if (count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count = 0;
		}
	}
}
