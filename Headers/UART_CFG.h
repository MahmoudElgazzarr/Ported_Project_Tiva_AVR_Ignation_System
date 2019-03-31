/*H**********************************************************************
* FILENAME :DataTypes.h
*
* DESCRIPTION :
*       Data Types

* PUBLIC FUNCTIONS : None
*
* NOTES :
*
*
* AUTHOR :    Mohamed AbdelKarim        START DATE :    19 Feb 19
*
* CHANGES : None
*
*
*H*/
#ifndef __UART_CFG_H__
#define __UART_CFG_H__

#include "Types.h"

#define BAUD_RATE    ((uint32) 9600)
#define FOSC	((uint32) 16000000)

typedef struct{
	uint32 BaudRate;
	uint8 No_StopBits;
	uint8 ParityMode;
	uint8 DataSize;
	uint8 SpeedMode;
	uint8 ClockPolarity;
}UART_Config;

extern UART_Config UART_Config_S;

enum UART_ClockPolarity_e{
	UART_RisingPol  = ((uint8) 0 ),
	UART_FallingPol = ((uint8) 1 ),
};


enum UART_NoStopBits_e{
	UART_OneStopBit  = ((uint8) 0 ),
	UART_TwoStopBit  = ((uint8) 1 ),
};

enum UART_ClockParity_e{
	UART_DisableParityBit = ((uint8) 0 ),
	UART_EvenParityBit    = ((uint8) 1 ),
	UART_OddParityBit     = ((uint8) 2 ),
};

enum UART_DataSize_e{
	UART_5_Bits = ((uint8) 5 ),
	UART_6_Bits = ((uint8) 6 ),
	UART_7_Bits = ((uint8) 7 ),
	UART_8_Bits = ((uint8) 8 ),
};

enum UART_SpeedMode_e{
	UART_NormalSpeedMode  = ((uint8) 0 ),
	UART_DoubleSpeedMode  = ((uint8) 1 ),
};


#endif
