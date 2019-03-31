/*
 * LCD.c
 *
 * Created: 2/19/2019 11:49:36 AM
 *  Author: Mahmoud Elgazzar
 */ 
#include "LCD.h"
#include "LCD_Cfg.h"
#include "Types.h"
#include "DIO.h"
#include "DIO_Definitions.h"
#include "avr/delay.h"


/*Inalization For The LCD*/

void LCD_init()
{
	#ifdef Bit_Mode4
	
	/*Data PINS*/
	DIO_SetPinDirection(LCD_D4 , OUTPUT);
	DIO_SetPinDirection(LCD_D5 , OUTPUT);
	DIO_SetPinDirection(LCD_D6 , OUTPUT);
	DIO_SetPinDirection(LCD_D7 , OUTPUT);
	/*Command Pins*/
	DIO_SetPinDirection(LCD_RS , OUTPUT);
	DIO_SetPinDirection(LCD_RW , OUTPUT);
	DIO_SetPinDirection(LCD_ENABLE , OUTPUT);
	
	LCD_sendCommand(LCD_CMD_INIT1_4_BIT);
	LCD_sendCommand(LCD_CMD_INIT2_4_BIT);
	/*Send Command To Set 4-Bit Mode*/
	LCD_sendCommand(Function_Set_4Bit);
	/*Turn On Cyrser */
	LCD_sendCommand(Cyrser_On);
	/*Clear Display*/
	LCD_sendCommand(Clear_Command);
	/*Increment Curser*/
	LCD_sendCommand(LCD_CMD_INCREMNT_CURSER);
	
	
	#endif
	
	#ifdef Bit_Mode8
	
	/ *Data Pins* /
	DIO_SetPinDirection(LCD_D0 , OUTPUT);
	DIO_SetPinDirection(LCD_D1 , OUTPUT);
	DIO_SetPinDirection(LCD_D2 , OUTPUT);
	DIO_SetPinDirection(LCD_D3 , OUTPUT);
	
	DIO_SetPinDirection(LCD_D4 , OUTPUT);
	DIO_SetPinDirection(LCD_D5 , OUTPUT);
	DIO_SetPinDirection(LCD_D6 , OUTPUT);
	DIO_SetPinDirection(LCD_D7 , OUTPUT);
	
	/ *Command Pins* /
	DIO_SetPinDirection(LCD_RS , OUTPUT);
	DIO_SetPinDirection(LCD_RW , OUTPUT);
	//DIO_SetPinDirection(LCD_ENABLE , OUTPUT);
	
	
	#endif
	
}

/*Function the sends Commands the The LCD Like Clear and So on*/

void LCD_sendCommand(uint8_t Cmd)
{
	/*RS == 0 For Command Register*/
	DIO_WritePin(LCD_RS,LOW);
	/*R/W == 0 For Writing */
	DIO_WritePin(LCD_RW , LOW);
	
	/*LCD Enable Pin LOW For Latching*/
	DIO_WritePin(LCD_ENABLE,LOW);
	
	/* Send Command Sequance */
	LCD_PORT = ( LCD_PORT & Mask_First_4Bits ) | ( Cmd & Mask_Last_4Bits );
	 
	/*Latching Sequance*/
	DIO_WritePin(LCD_ENABLE,HIGH);
	_delay_ms(2);
	/*LOW For Enable to Latch*/
	DIO_WritePin(LCD_ENABLE,LOW);
	
	
	/*LCD Enable Pin LOW For Latching*/
	DIO_WritePin(LCD_ENABLE,LOW);
	/*Send Command*/
	LCD_PORT = ( LCD_PORT & Mask_First_4Bits ) | ( Cmd << Number_Four ); 
	
	/*Latching Sequance*/
	DIO_WritePin(LCD_ENABLE,HIGH);
	_delay_ms(2);
	/*LOW For Enable to Latch*/
	DIO_WritePin(LCD_ENABLE,LOW);
	_delay_ms(2);
}

/*Function To Display Char on the LCD*/
void LCD_displayChar(uint8_t ch)
{
	/*RS == 1 For Data Register*/
	DIO_WritePin(LCD_RS,HIGH);
	/*R/W == 0 For Writing */
	DIO_WritePin(LCD_RW , LOW);
	
	/*LCD Enable Pin LOW For Latching*/
	DIO_WritePin(LCD_ENABLE,LOW);
	
	/* Send Command Sequance */
	LCD_PORT = ( LCD_PORT & Mask_First_4Bits ) | ( ch & Mask_Last_4Bits );
	
	/*Latching Sequance*/
	DIO_WritePin(LCD_ENABLE,HIGH);
	_delay_ms(2);
	/*LOW For Enable to Latch*/
	DIO_WritePin(LCD_ENABLE,LOW);
	
	
	/*LCD Enable Pin LOW For Latching*/
	DIO_WritePin(LCD_ENABLE,LOW);
	/*Send Command*/
	LCD_PORT = ( LCD_PORT & Mask_First_4Bits ) | ( ch << Number_Four );
	
	/*Latching Sequance*/
	DIO_WritePin(LCD_ENABLE,HIGH);
	_delay_ms(2);
	/*LOW For Enable to Latch*/
	DIO_WritePin(LCD_ENABLE,LOW);
	_delay_us(100);
	
}
/*Function that Takes array of char*/
void LCD_displayString(uint8_t str[])
{
	/*Variable For for Loop*/
	uint8_t i=0;
	
	while(str[i]!= 0)
	{
		_delay_ms(5);
		LCD_displayChar(str[i]);
		_delay_ms(5);
		i++;
	}
}

/*Display String Row and Column*/
void LCD_displayStringRowColumn(uint8_t str[],uint8_t Row,uint8_t Column)
{
	LCD_gotoRowColumn(Row,Column);
	LCD_displayString(str);
}
/* Function to clear LCD */
void LCD_clear()
{
	LCD_sendCommand(Clear_Command);
}
/*
* ROW : Enter #define from .h file LCD_CMD_1ST_LINE
* Column : Enter Number from 0 to 15
*/
void LCD_gotoRowColumn(uint8_t Row,uint8_t Column)
{
	LCD_sendCommand(Row+Column);
}
