/*
 * LightSensor.h
 *
 *  Created on: Dec 11, 2023
 *      Author: Gp Team
 */

#ifndef INC_LIGHTSENSOR_H_
#define INC_LIGHTSENSOR_H_

/*Library functions*/
void LightSensor_voidInit(void);
void LightSensor_uint8ReadIntensity(uint16_t *Copy_puint16LuxValue);
void LightSensor_voidCallBackFunction(uint16_t Copy_uint16LowerThreshold,uint16_t Copy_uint16UpperThreshold);
void LightSensor_voidSetInterruptTest(void);
void LightSensor_voidClearInterrupt(void);


/*TSL2561 slave address*/
#define LightSensor_SLAVE_ADDRESS  ((0x39) << 1)

/*TSL2561 Channel*/
#define LightSensor_I2CChannel          &hi2c2

/*Registers addresses*/
/*
 * Register Map
 */

#define TSL2561_REG_CONTROL				    0x00
#define TSL2561_REG_TIMING				    0x01
#define TSL2561_REG_THRESHLOWLOW			0x02
#define TSL2561_REG_THRESHLOWHIGH			0x03
#define TSL2561_REG_THRESHHIGHLOW			0x04
#define TSL2561_REG_THRESHHIGHHIGH			0x05
#define TSL2561_REG_INTERRUPT				0x06
#define TSL2561_REG_CRC					    0x08
#define TSL2561_REG_ID					    0x0A
#define TSL2561_REG_DATA0LOW				0x0C
#define TSL2561_REG_DATA0HIGH				0x0D
#define TSL2561_REG_DATA1LOW				0x0E
#define TSL2561_REG_DATA1HIGH				0x0F




#define TSL2561_COMMAND_NORMAL              0x80
#define TSL2561_COMMAND_STATE_CLEAR  		0x40

#define TSL2561_Max_Delay                   1000


#endif /* INC_LIGHTSENSOR_H_ */
