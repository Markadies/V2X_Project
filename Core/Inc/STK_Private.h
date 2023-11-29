/********************************************/
/* SWC: STK Driver                          */
/* Author: Bendary                          */
/* Version: v0.0                            */
/* Date: 20 OCT 2023                        */
/* Description: This is the implem. of STK  */
/********************************************/
/*File Guard*/
#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

/*Base address is 0xE000E010, but no need for structs*/
/*I will define directly the registers*/

#define STK_CTRL     *((volatile uint32_t*)0xE000E010)

#define STK_CTRL_ENABLE              0
#define STK_CTRL_TICKINT             1
#define STK_CTRL_CLKSOURCE           2
#define STK_CTRL_COUNTFLAG           16

#define STK_LOAD     *((volatile uint32_t*)0xE000E014) //From bit 0 to 23
#define STK_VAL      *((volatile uint32_t*)0xE000E018) //From bit 0 to 23
#define STK_CALIB    *((volatile uint32_t*)0xE000E01C)

/*Macros*/

/*Clock source to be configured*/
#define AHB                      0
#define AHB_Over_8               1

/*Macros to define the interval for the interrupt*/
#define SingleMode           0
#define PeriodicMode         1

#endif
