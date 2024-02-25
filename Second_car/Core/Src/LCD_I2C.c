/*
 * LCD_I2C.c
 *
 *  Created on: Nov 30, 2023
 *      Author: Bendary
 */

#include "main.h"
#include "stm32f4xx_hal.h"
#include "LCD_I2C.h"
#include "stm32f4xx_hal_i2c.h"

#define LCD_SLAVE_ADDRESS 0b01001110

extern I2C_HandleTypeDef hi2c1;

void LCD_voidInit(void)
{
	/*Setting 4 bits interface(Twice as the datasheet specefies)*/
	LCD_voidSendCommand(0b00110011);
	LCD_voidSendCommand(0b00110010);
	HAL_Delay(50);
	/*Setting the LCD Function*/
	LCD_voidSendCommand(0b00101000);
	HAL_Delay(50);
	/*Clearing the display*/
	LCD_voidSendCommand(0b00000001);
	HAL_Delay(50);
	/*Set the entry mode*/
	LCD_voidSendCommand(0b00000110);
	HAL_Delay(50);
	/*Set the display to on*/
	LCD_voidSendCommand(0b00001100);
	HAL_Delay(50);
	/*Set the cursor to home */
	LCD_voidSendCommand(0b00000010);
	HAL_Delay(50);
	/*and the Data address to 0*/
	LCD_voidSendCommand(0b10000000);

}
void LCD_voidSendCommand(uint8_t Copy_uint8Command)
{
	uint8_t Local_uint8Local_uint8DataU,Local_uint8Local_uint8DataL;
	uint8_t Local_uint8Local_uint8DataT[4];

	/*0b00110011 & 0b11110000  --> 0b00110000--> DataU
	 * 0b00110011 << 4 -->  0b00110000 & 0b11110000--> 0b00110000
	 *
	 * (DataU)0b00110000 | 0b00001100 --> 0b00111100
	 *  //
	 *
	 *               | 0b00001000 --> 0b00111000
	 *
	 *
	 *
	 *  0b00110010 & 0b11110000 --> 0b00110000 datau
	 *  0b00110010 << 4 --> 0b00100000 & 0b11110000 --> 0b00100000 dataL
	 *  0b00110000 | 0b00001100 --> 0b00111100
	 *  0b00110000 | 0b00001000 --> 0b00111000
	 *
	 *  0b00100000 | 0b00001100  --> 0b00101100
	 *  0b00100000 | 0b00001000  --> 0b00101000
	 * */

/*0b00101000 & 0b11110000 --> 0b00100000
 *0b
 *
 *
 * 0b00000001 --> DataU --> 0b000000000-->0b00000001100
 *
 * */
	Local_uint8Local_uint8DataU=(Copy_uint8Command&0b11110000);
	Local_uint8Local_uint8DataL=((Copy_uint8Command<<4)&0b11110000);

	Local_uint8Local_uint8DataT[0]=Local_uint8Local_uint8DataU|0b00001100; //EN=1 RS=0
	Local_uint8Local_uint8DataT[1]=Local_uint8Local_uint8DataU|0b00001000; //EN=0 RS=0
	Local_uint8Local_uint8DataT[2]=Local_uint8Local_uint8DataL|0b00001100; //EN=1 RS=0
	Local_uint8Local_uint8DataT[3]=Local_uint8Local_uint8DataL|0b00001000; //EN=0 RS=0

	HAL_I2C_Master_Transmit(&hi2c1, LCD_SLAVE_ADDRESS,(uint8_t*)Local_uint8Local_uint8DataT , 4, 100);
}

void LCD_voidSendCharachter(uint8_t Copy_uint8Charachter)
{
	uint8_t Local_uint8Local_uint8DataU,Local_uint8Local_uint8DataL;
	uint8_t Local_uint8Local_uint8DataT[4];
	Local_uint8Local_uint8DataU=(Copy_uint8Charachter&0b11110000);
	Local_uint8Local_uint8DataL=((Copy_uint8Charachter<<4)&0b11110000);

	Local_uint8Local_uint8DataT[0]=Local_uint8Local_uint8DataU|0b00001101; //EN=1 RS=0
	Local_uint8Local_uint8DataT[1]=Local_uint8Local_uint8DataU|0b00001001; //EN=0 RS=0
	Local_uint8Local_uint8DataT[2]=Local_uint8Local_uint8DataL|0b00001101; //EN=1 RS=0
	Local_uint8Local_uint8DataT[3]=Local_uint8Local_uint8DataL|0b00001001; //EN=0 RS=0
	HAL_I2C_Master_Transmit(&hi2c1, LCD_SLAVE_ADDRESS,(uint8_t*)Local_uint8Local_uint8DataT , 4, 100);

}

void LCD_voidSendString (uint8_t *Copy_pu8StringOfCharachters)
{
	uint8_t Local_uint8Counter=0;
	while(Copy_pu8StringOfCharachters[Local_uint8Counter] !='\0')
	{
		LCD_voidSendCharachter(Copy_pu8StringOfCharachters[Local_uint8Counter]);
		Local_uint8Counter++;
	}


}
void LCD_voidSetPositionXY(uint8_t Copy_uint8Row,uint8_t Copy_uint8Column)
{
	//1,add,add,add,add,add,add,add,0,0
	uint8_t Local_uint8PositionAddress = 0b10000000;
	switch(Copy_uint8Row){
	case 0:
		Local_uint8PositionAddress = Local_uint8PositionAddress | (Copy_uint8Column + 0);
		break;
	case 1:
		Local_uint8PositionAddress = Local_uint8PositionAddress | (Copy_uint8Column + 64);
		break;
	case 2:
		Local_uint8PositionAddress = Local_uint8PositionAddress | (Copy_uint8Column + 20);
		break;
	case 3:
		Local_uint8PositionAddress = Local_uint8PositionAddress | (Copy_uint8Column + 84);
		break;
	}
		LCD_voidSendCommand(Local_uint8PositionAddress);
		HAL_Delay(1);

}

void LCD_voidClearDisplay(void)
{
	/*Clearing the display by command 0b00000001*/
	LCD_voidSendCommand(0b00000001);
}

void LCD_voidWriteNum(uint32_t Copy_uint32Number)
{
	uint8_t Local_uint8FirstDigit=0;
	for(uint32_t i=1000000000;i>0;i/=10)
	{
	    if(Copy_uint32Number/i>0)
		{
	    	LCD_voidSendCharachter(Copy_uint32Number/i+48);
			Copy_uint32Number%=i;
			Local_uint8FirstDigit=1;
		}
		// print 0 after the first digit
		else if(Local_uint8FirstDigit==1)
		{
			LCD_voidSendCharachter(48);
		}
	}
}

void LCD_voidDrawSpecialCharachter(uint8_t*Copy_puint8Pattern,uint8_t Copy_uint8LocationNum,uint8_t Copy_uint8RowNum,uint8_t Copy_uint8ColNum)
{
	/*Accessing the CGRAM address*/
	uint8_t Local_uint8CGRAMAddress,Local_uint8Counter;
	Local_uint8CGRAMAddress=Copy_uint8LocationNum*8;

	/*Accessing CGRAM of lcd by command 0b01xxxxxx*/
	LCD_voidSendCommand(Local_uint8CGRAMAddress+64);

	/*Write the pattern on CGRAM*/
	/*zy makont ba3mel fel string ha3mel hena , bas al fekra ane hawa2f al loop 3nd (((8))) ale howa max bytes
	 * in a location in the CGRAM fal user masaln e5tar location 0 fa2a5ro feh 8 charachters ale homa 8 bytes*/
	for(Local_uint8Counter=0;Local_uint8Counter<8;Local_uint8Counter++)
	{
		LCD_voidSendCharachter(Copy_puint8Pattern[Local_uint8Counter]);
	}

	/*Keda e7na 7atena al pattern fe location mo3yn fel CGRAM, fa na2esna bas neb3at al pattern lel DDRAM 34an n7oto fel LCD */
	/*kona fo2 3malna command 34an ne access al CGRAM 34an ne access al DDRAM lazem command tany
	 * wel set position feha asln al command dah*/
	LCD_voidSetPositionXY(Copy_uint8RowNum,Copy_uint8ColNum);
	LCD_voidSendCharachter(Copy_uint8LocationNum);
}

