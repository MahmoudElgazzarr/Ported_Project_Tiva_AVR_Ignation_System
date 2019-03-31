/*
 * LCD.h
 *
 * Created: 2/19/2019 11:50:16 AM
 *  Author: AVE-LAP-040
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "stdint.h"

void LCD_init();

void LCD_displayChar(uint8_t ch);
void LCD_sendCommand(uint8_t Cmd);
/* if you are  sending array of chars you must put null terminator at the end */
void LCD_displayString(uint8_t str[]);

void LCD_displayStringRowColumn(uint8_t str[],uint8_t Row,uint8_t Column);

void LCD_clear();
void LCD_gotoRowColumn(uint8_t Row,uint8_t Column);


#define Mask_Last_4Bits 0xF0
#define Mask_First_4Bits 0x0F
#define Number_Four 4


#endif /* LCD_H_ */