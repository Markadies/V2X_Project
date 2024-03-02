/*
 * GPS.h
 *
 *  Created on: Dec 5, 2023
 *      Author: dell
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

/****************************Macros***************************/
#define  Decode_Success  1
#define  Decode_Failed   2

/*Waits till the gps gets right information and its done*/
void GPS_voidInit(void);

/*Decode the message and puts the important information in the global varialbles
 * like: longitude, latitude, North/south , East/west*/
uint8_t GPS_uint8DecodeGGAData(void);

/*Function to send the GPS data (latitude,long,E/W,N/S) to the LCD */
void GPS_voidLCD_Data_Display(void);

/*Function to send the GPS data (latitude,long,E/W,N/S) to the LCD */
void GPS_voidESP_Data_Send(void);


#endif /* INC_GPS_H_ */
