/*
 * Build_msg.c
 *
 *  Created on: Feb 29, 2024
 *      Author: dell
 */

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "Build_msg.h"


void GPSSPEED_voidBuildMsg(uint8_t* Msg_Array,double Copy_doubleGPS_Longitude,double Copy_doubleGPS_Latitude,uint16_t Copy_uint16Speed)
{

uint8_t Local_uint8LatitudeArr[11];
uint8_t Local_uint8LongitudeArr[11];
uint8_t Local_uint8SpeedElements;

uint8_t Local_uint8Counter=0;
if(Copy_uint16Speed<10)
{
	Local_uint8SpeedElements=1;
}
else if(Copy_uint16Speed<100)
{
	Local_uint8SpeedElements=2;
}
else if((Copy_uint16Speed>100) && (Copy_uint16Speed<1000))
{
	Local_uint8SpeedElements=3;
}
else
{
	Local_uint8SpeedElements=4;
}
uint8_t Local_uint8SpeedArr[Local_uint8SpeedElements+1];

 /*Putting the lat and lon in a string form to be sent to the esp*/
 snprintf(&Local_uint8LongitudeArr,sizeof(Local_uint8LongitudeArr),"%.6f",Copy_doubleGPS_Longitude);
 snprintf(&Local_uint8LatitudeArr,sizeof(Local_uint8LatitudeArr),"%.6f",Copy_doubleGPS_Latitude);

 snprintf(&Local_uint8SpeedArr,sizeof(Local_uint8SpeedArr),"%d",Copy_uint16Speed);

 Msg_Array[0]='#';
 Msg_Array[1]=Local_uint8LongitudeArr[0];
 Msg_Array[2]=Local_uint8LongitudeArr[1];
 Msg_Array[3]=Local_uint8LongitudeArr[2];
 Msg_Array[4]=Local_uint8LongitudeArr[3];

 Msg_Array[5]=Local_uint8LongitudeArr[4];
 Msg_Array[6]=Local_uint8LongitudeArr[5];
 Msg_Array[7]=Local_uint8LongitudeArr[6];
 Msg_Array[8]=Local_uint8LongitudeArr[7];
 Msg_Array[9]=Local_uint8LongitudeArr[8];

 Msg_Array[10]='*';

 Msg_Array[11]= Local_uint8LatitudeArr[0];
 Msg_Array[12]= Local_uint8LatitudeArr[1];
 Msg_Array[13]= Local_uint8LatitudeArr[2];
 Msg_Array[14]= Local_uint8LatitudeArr[3];
 Msg_Array[15]= Local_uint8LatitudeArr[4];
 Msg_Array[16]= Local_uint8LatitudeArr[5];
 Msg_Array[17]= Local_uint8LatitudeArr[6];
 Msg_Array[18]= Local_uint8LatitudeArr[7];
 Msg_Array[19]= Local_uint8LatitudeArr[8];

 Msg_Array[20]= '&';


 for(Local_uint8Counter;Local_uint8Counter<Local_uint8SpeedElements;Local_uint8Counter++)
 {
	 Msg_Array[21+Local_uint8Counter]=Local_uint8SpeedArr[Local_uint8Counter];
 }

Msg_Array[21+Local_uint8Counter]='^';

}

