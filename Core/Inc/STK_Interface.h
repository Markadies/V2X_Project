/********************************************/
/* SWC: STK Driver                          */
/* Author: Bendary                          */
/* Version: v0.0                            */
/* Date: 20 OCT 2023                        */
/* Description: This is the implem. of STK  */
/********************************************/
/*File Guard*/
#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

void STK_voidInit(void);
void STK_voidSetBusyWait(uint32_t Copy_uint32_tTimeInMillis);
void STK_voidSetIntervalSingle(uint32_t Copy_uint32_tTimeInMillis,void (*LPF) (void));
void STK_voidSetIntervalPeriodic(uint32_t Copy_uint32_tTimeInMillis,void (*LPF)(void));
uint32_t STK_voidGetElapsedTime(void);
uint32_t STK_voidGetRemainingTime(void);

#endif
