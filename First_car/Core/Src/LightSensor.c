/*
 * LightSensor.c
 *
 *  Created on: Dec 11, 2023
 *      Author: GP Team
 */
#include "stm32f4xx_hal.h"
#include "main.h"
#include "stm32f4xx_hal_i2c.h"
#include "LightSensor.h"
#include "math.h"


extern I2C_HandleTypeDef hi2c2;

/*Global pointer to function to send the ISR defined by user to the Handler in the it.c file
 * using the call back function*/
//void (*Global_voidISRPtrToFunc)(void)=NULL;


/*Static functions*/
static void TSL2561_Reset(void);
static void TSL2561_GetChannelsReadings(uint16_t* Copy_uint16Data0Val, uint16_t* Copy_uint16Data1Val);
static void TSL2561_WriteByte(uint8_t Copy_uint8RegisterAddress, uint8_t Copy_uint8RegisterValue);
static void TSL2561_ReadByte(uint8_t Copy_uint8RegisterAddress, uint8_t *Copy_puinit8RecivingVariable);

void LightSensor_voidInit(void)
{

	/*Powering up the module*/

	/*1-first element is the command -> Address of control register
	 * 2-Second element is the 0b00000011 which power up the module */
	TSL2561_WriteByte((TSL2561_COMMAND_NORMAL|TSL2561_REG_CONTROL),0b00000011);


	/*1- first element is the command -> Address of timing register
	 *2- Second element is the 0b00010010 which makes the gain = 1 and the integration time
	 *2- =402ms which is the default value*/

	TSL2561_WriteByte((TSL2561_COMMAND_NORMAL|TSL2561_REG_TIMING),0b00000010);


}

void LightSensor_uint8ReadIntensity(uint16_t *Copy_puint16LuxValue)
{
	//Variables for storing Data registers
	uint16_t Local_uint16Channel0Val, Local_uint16Channel1Val,flux_integar=0;
	float flux=0;

	//Get the values from the data registers
	TSL2561_GetChannelsReadings(&Local_uint16Channel0Val, &Local_uint16Channel1Val);
	/*Calculating the lux for T, FN, and CL Package of the sensor*/

	//Calculate the ratio of the PhotoDiodes
	float Ratio = ((float)Local_uint16Channel1Val) / ((float)Local_uint16Channel0Val);

	//Calculating Lux
	//Ratio between 0 and 0.50

	if(Ratio <= 0.50)
	{
		flux= (0.0304 * Local_uint16Channel0Val) - (0.062* Local_uint16Channel0Val * pow(Ratio, 1.4));
	}

	//If the ratio is between 0.51 and 0.61
	else if(Ratio <= 0.61)
	{
		flux = (0.0224 * Local_uint16Channel0Val) - (0.031 * Local_uint16Channel1Val);
	}

	//If the Ratio is between 0.62 and 0.81
	else if(Ratio <= 0.80)
	{
		flux = (0.0128 * Local_uint16Channel0Val) - (0.0153 * Local_uint16Channel1Val);
	}

	//If the Ratio is between 0.82 and 1.39
	else if(Ratio <= 1.30)
	{
		flux = (0.00146 * Local_uint16Channel0Val) - (0.00112 * Local_uint16Channel1Val);
	}

	//If the Ratio is bigger than 1.30
	else
	{
		flux = 0;
	}

	flux_integar=round(flux);

	/*Update the user variable*/
	*Copy_puint16LuxValue=flux_integar;

	/*Reseting the chip if the Sensor produces high flux */
	/*
	if(flux_integar>200)
	{
      TSL2561_Reset();
	}
	 */

}

void LightSensor_voidCallBackFunction(uint16_t Copy_uint16LowerThreshold,uint16_t Copy_uint16UpperThreshold)
{
	uint8_t Local_uint8LowLowThreshold,Local_uint8LowHighThreshold,Local_uint8HighLowThreshold,Local_uint8HighHighThreshold;


	/*Checking if the user sent function address is null or not to sent it to the Handler*/

	//if(Copy_voidISR_PtrToFunc!=NULL)
	//{
		/*Assigning the user function to the global pointer to function to be sent to the EXTI handler*/
	//	Global_voidISRPtrToFunc=Copy_voidISR_PtrToFunc;
	//}

   /*Performing bitwise operations to divide the 16 bit in upper and lower threshold into 8 bits each to be sent to the registers*/

	Local_uint8LowLowThreshold=(Copy_uint16LowerThreshold & 0x00FF);
	Local_uint8LowHighThreshold= (Copy_uint16LowerThreshold >>8);
    Local_uint8HighLowThreshold=(Copy_uint16UpperThreshold & 0x00FF);
    Local_uint8HighHighThreshold= (Copy_uint16UpperThreshold >>8);

    /*Setting the thresholds of channel 0 value to the user defined ones*/

    TSL2561_WriteByte((TSL2561_COMMAND_NORMAL | TSL2561_REG_THRESHLOWLOW), Local_uint8LowLowThreshold);
    TSL2561_WriteByte((TSL2561_COMMAND_NORMAL | TSL2561_REG_THRESHLOWHIGH), Local_uint8LowHighThreshold);
    TSL2561_WriteByte((TSL2561_COMMAND_NORMAL | TSL2561_REG_THRESHHIGHLOW), Local_uint8HighLowThreshold);
    TSL2561_WriteByte((TSL2561_COMMAND_NORMAL | TSL2561_REG_THRESHHIGHHIGH), Local_uint8HighHighThreshold);

        /*1- first element is the command -> Address of interrupt register
    	 *2- Second element is the 0b00010101 which activates the level interrupt for the module
    	 *and make the interrupt when the intensity value exceeds the limits of the
    	 *threshold for 1 integration cycles (2sec)*/

    	TSL2561_WriteByte((TSL2561_COMMAND_NORMAL|TSL2561_REG_INTERRUPT), 0b00010000);

    	/*Clear any pending interrupt*/
    	//HAL_I2C_Master_Transmit(LightSensor_I2CChannel, LightSensor_SLAVE_ADDRESS, TSL2561_COMMAND_STATE_CLEAR, 1, TSL2561_Max_Delay);
    	//TSL2561_WriteByte(TSL2561_COMMAND_STATE_CLEAR,0);

}

void LightSensor_voidSetInterruptTest(void)
{
	/*Setting the interrupt of the tsl*/
TSL2561_WriteByte((TSL2561_COMMAND_NORMAL | TSL2561_REG_INTERRUPT),0b00110101);

}
void LightSensor_voidClearInterrupt(void)
{
	TSL2561_WriteByte((TSL2561_COMMAND_NORMAL | TSL2561_REG_INTERRUPT), 0b00000000);

}

static void TSL2561_GetChannelsReadings(uint16_t* Copy_uint16Data0Val, uint16_t* Copy_uint16Data1Val)
{
	//Variables for storing received data
	uint8_t data0Low, data0High, data1Low, data1High;

	//Read Data0 registers
	TSL2561_ReadByte((TSL2561_COMMAND_NORMAL|TSL2561_REG_DATA0LOW),	&data0Low);
	TSL2561_ReadByte((TSL2561_COMMAND_NORMAL|TSL2561_REG_DATA0HIGH), &data0High);

	//Read Data1 registers
	TSL2561_ReadByte((TSL2561_COMMAND_NORMAL|TSL2561_REG_DATA1LOW),	&data1Low);
	TSL2561_ReadByte((TSL2561_COMMAND_NORMAL|TSL2561_REG_DATA1HIGH), &data1High);

	//Combine Data register values into single 16 bit variable
	*Copy_uint16Data0Val = data0High * 256 + data0Low;
	*Copy_uint16Data1Val = data1High * 256 + data1Low;

}

static void TSL2561_Reset(void)
{
	/*Reseting the chip*/

	/*Power off the module*/
	TSL2561_WriteByte((TSL2561_COMMAND_NORMAL|TSL2561_REG_CONTROL),0b00000000);
	HAL_Delay(20);

	/*Initializing it again*/
	LightSensor_voidInit();

}

static void TSL2561_WriteByte(uint8_t Copy_uint8RegisterAddress, uint8_t Copy_uint8RegisterValue)
{
	HAL_I2C_Mem_Write(LightSensor_I2CChannel, LightSensor_SLAVE_ADDRESS,Copy_uint8RegisterAddress, 1, &Copy_uint8RegisterValue,1,TSL2561_Max_Delay);
}

static void TSL2561_ReadByte(uint8_t Copy_uint8RegisterAddress, uint8_t *Copy_puinit8RecivingVariable)
{
	HAL_I2C_Mem_Read(LightSensor_I2CChannel, LightSensor_SLAVE_ADDRESS,Copy_uint8RegisterAddress, 1, Copy_puinit8RecivingVariable, 1,TSL2561_Max_Delay);
}


