/*
 * Help_Functions.c
 *
 *  Created on: Feb 25, 2024
 *      Author: dell
 */

#include "stm32f4xx_hal.h"
#include "Help_Functions.h"
#include "LCD_I2C.h"

/***************************************Static Functions Definition***********************************************/
static void LCD_Print_WarningSign(void);

void LCD_HighLightIntensity_Warning()
{

	/*Printing the warning sign*/
	LCD_Print_WarningSign();

	/*Printing the warning message to the driver*/
	LCD_voidSetPositionXY(1,0);
	LCD_voidSendString("Dim your");

	LCD_voidSetPositionXY(2,0);
	LCD_voidSendString("Light ASAP!");

}


void LCD_AvoidHardBraking(void)
{
	/*Printing the warning sign*/
	LCD_Print_WarningSign();

	/*Printing the warning message to the driver*/
	LCD_voidSetPositionXY(1,0);
	LCD_voidSendString("Hit Brakes");

	LCD_voidSetPositionXY(2,3);
	LCD_voidSendString("ASAP!!!");

}


void LCD_AvoidOvertaking_Warning()
{

	/*Printing the warning sign*/
	LCD_Print_WarningSign();

	/*Printing the warning message to the driver*/
	LCD_voidSetPositionXY(1,4);
	LCD_voidSendString("DONT");

	LCD_voidSetPositionXY(2,0);
	LCD_voidSendString("OVERTAKE!!!");


}

void LCD_BeingOvertaken_Warning()
{

	/*Printing the warning sign*/
	LCD_Print_WarningSign();

	/*Printing the warning message to the driver*/
	LCD_voidSetPositionXY(1,4);
	LCD_voidSendString("Slow Down");


}
static void LCD_Print_WarningSign(void)
{
	/*Saving the elemetents of each block of the LCD in multiple arrays to be sent to the special charachter function*/

	uint8_t LCD_R1_C16_Array[8] =
	{
			0b00000100,
			0b00001010,
			0b00010001,
			0b00000000,
			0b00000000,
			0b00001110,
			0b00001110,
			0b00001110
	};

	uint8_t LCD_R1_C17_Array[8] =
	{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00010000,
			0b00001000,
			0b00000100,
			0b00000010,
			0b00000001
	};
	uint8_t LCD_R1_C15_Array[8] =
	{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000001,
			0b00000010,
			0b00000100,
			0b00001000,
			0b00010000
	};

	uint8_t LCD_R2_C14_Array[8] =
	{
			0b00000010,
			0b00000100,
			0b00001000,
			0b00010000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00011111
	};

	uint8_t LCD_R2_C18_Array[8] =
	{
			0b00001000,
			0b00000100,
			0b00000010,
			0b00000001,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00011111
	};
	uint8_t LCD_R2_C13_Array[8] =
	{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000001,
			0b00000010,
			0b00000100,
			0b00011111
	};
	uint8_t LCD_R2_C19_Array[8] =
	{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00010000,
			0b00001000,
			0b00000100,
			0b00000010,
			0b00011111
	};
	uint8_t LCD_R2_C15_Array[8] =
	{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00011111
	};
	uint8_t LCD_R2_C17_Array[8] =
	{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00011111
	};
	uint8_t LCD_R2_C16_Array[8] =
	{
			0b00001110,
			0b00001110,
			0b00001110,
			0b00000000,
			0b00000100,
			0b00000000,
			0b00000000,
			0b00011111
	};


	LCD_voidDrawSpecialCharachter(&LCD_R1_C15_Array, 0, 1, 15);
	LCD_voidDrawSpecialCharachter(&LCD_R1_C16_Array, 1, 1, 16);
	LCD_voidDrawSpecialCharachter(&LCD_R1_C17_Array, 2, 1, 17);

	LCD_voidDrawSpecialCharachter(&LCD_R2_C14_Array, 3, 2, 14);
	LCD_voidDrawSpecialCharachter(&LCD_R2_C15_Array, 4, 2, 15);
	LCD_voidDrawSpecialCharachter(&LCD_R2_C16_Array, 5, 2, 16);
	LCD_voidDrawSpecialCharachter(&LCD_R2_C17_Array, 6, 2, 17);
	LCD_voidDrawSpecialCharachter(&LCD_R2_C18_Array, 7, 2, 18);




}






