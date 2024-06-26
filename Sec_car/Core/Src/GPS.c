/*
 * GPS.c
 *
 *  Created on: Dec 5, 2023
 *      Author: GP Team
 */
#include "main.h"
#include "stm32f4xx_hal.h"
#include "GPS.h"
#include "NMEA.h"
#include "UartRingbuffer.h"
#include "LCD_I2C.h"
#include <math.h>



#define  Valid_Data      2
#define  unValid_Data    1



/*This is the buffer which contains th undecoded GGA data*/
uint8_t GGA[100];

/*This is the NMEA Structed data */
GPSSTRUCT GPS_NMEA_DATA;

/*This is the GGA flag to check the data is valid or not*/
uint8_t flagGGA=0;

/*GPS flag to determine the gps decoding successful or not*/
uint8_t  flag_GPS;
extern UART_HandleTypeDef huart1;

/*This is the object of our struct*/
GPS_Data_t GPS_Data;

/*Waits till the gps gets right information and its done*/
void GPS_voidInit(void)
{
	/*Ring Buffer initialization*/
	Ringbuf_init();
	HAL_Delay(500);

	/* LCD clear */
	LCD_voidClearDisplay();

	/*Writing on LCD that the gps still warming up*/
	LCD_voidSetPositionXY(0,2);
	LCD_voidSendString("Waiting for GPS");

	/*waiting till the GGA data is valid*/
	while(flagGGA!=Valid_Data)
	{
		if (Wait_for("GGA") == 1)
		{
			Copy_upto("*", GGA);
			if (decodeGGA(GGA, &GPS_NMEA_DATA.ggastruct) == 0) flagGGA = Valid_Data;  // 2 indicates the data is valid
			else flagGGA = unValid_Data;  // 1 indicates the data is invalid
		}
	}

	/*Clearing the LCD and telling the user to start the project */
	LCD_voidClearDisplay();
	LCD_voidSetPositionXY(0,4);
	LCD_voidSendString("GPS is done");
	LCD_voidSetPositionXY(1,4);
	LCD_voidSendString("good 2 go");

	/*Clearing the flag*/
	flagGGA=0;
	HAL_Delay(1000);

	/*Clearing the LCD*/
	LCD_voidClearDisplay();

}

/*Decode the message and puts the important information in the global variables
 * like: longitude, latitude, North/south , East/west*/

/*Returns 1 in success and 2 if the decoding process failed*/
uint8_t GPS_uint8DecodeGGAData()
{
	uint8_t Local_uint8ErrorCode=0;

	if (Wait_for("GGA") == 1)
	{
		Copy_upto("*", GGA);
		if (decodeGGA(GGA, &GPS_NMEA_DATA.ggastruct) == 0) flagGGA = Valid_Data;  // 2 indicates the data is valid
		else flagGGA = unValid_Data;  // 1 indicates the data is invalid
	}

	if(flagGGA==Valid_Data)
	{
		Local_uint8ErrorCode=Decode_Success;
		GPS_Data.Latitude    =    GPS_doubleLongLat_Calculation(GPS_NMEA_DATA.ggastruct.lcation.latitude);
		GPS_Data.Longitude   =    GPS_doubleLongLat_Calculation(GPS_NMEA_DATA.ggastruct.lcation.longitude);

		GPS_Data.East_West = GPS_NMEA_DATA.ggastruct.lcation.EW;
		GPS_Data.North_South = GPS_NMEA_DATA.ggastruct.lcation.NS;
	}
	else
	{
		Local_uint8ErrorCode=Decode_Failed;
	}


	return Local_uint8ErrorCode;
}

/*Function to send the GPS data (latitude,long,E/W,N/S) to the LCD */
void GPS_voidLCD_Data_Display(void)
{
	/*Clearing the lcd to send the needed data*/
	LCD_voidClearDisplay();

	/*Sending the data in this pattern:  */

	//Latitude sending
	LCD_voidSetPositionXY(0,0);
	LCD_voidSendString("Lat: ");
	LCD_voidSetPositionXY(0,6);
	LCD_voidWriteNum(GPS_Data.Latitude);

	//longitude sending
	LCD_voidSetPositionXY(1,0);
	LCD_voidSendString("Long: ");
	LCD_voidSetPositionXY(1,6);
	LCD_voidWriteNum(GPS_Data.Longitude);

	// E/W sending
	LCD_voidSetPositionXY(2,0);
	LCD_voidSendString("E/W: ");
	LCD_voidSetPositionXY(2,6);
	LCD_voidSendCharachter(GPS_Data.East_West);

	// N/S Sending
	LCD_voidSetPositionXY(2,10);
	LCD_voidSendString("N/S: ");
	LCD_voidSetPositionXY(2,16);
	LCD_voidSendCharachter(GPS_Data.North_South);


}

double GPS_doubleLongLat_Calculation(double lat)
{
	uint8_t intValue ;
	double fraction;
	intValue = lat; //intValue = 31 instead of 31.39049
	fraction = lat - intValue; // fraction = 0.39049
	fraction = (double) ((fraction * 100.0) / 60.0) ; //fraction = (39.049)/60 = 0.6532

	return (double) (intValue + fraction); // return value = 31 + 0.6532 = 31.6532
}

