/*
 * LCD_I2C.h
 *
 *  Created on: Nov 30, 2023
 *      Author: Bendary
 */

#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_

void LCD_voidInit(void);
void LCD_voidSendCommand(uint8_t Copy_uint8Command);
void LCD_voidSendCharachter(uint8_t Copy_uint8Charachter);
void LCD_voidSendString (uint8_t *Copy_pu8StringOfCharachters);
void LCD_voidSetPositionXY(uint8_t Copy_uint8Row,uint8_t Copy_uint8Column);
void LCD_voidClearDisplay(void);
void LCD_voidWriteNum(uint32_t Copy_uint32Number);
void LCD_voidDrawSpecialCharachter(uint8_t*Copy_puint8Pattern,uint8_t Copy_uint8LocationNum,uint8_t Copy_uint8RowNum,uint8_t Copy_uint8ColNum);

#endif /* INC_LCD_I2C_H_ */
