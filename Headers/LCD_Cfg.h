/*
 * LCD_Cfg.h
 *
 * Created: 2/19/2019 11:51:26 AM
 *  Author: AVE-LAP-040
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/*define F_CPU Frequancy*/
#define  F_CPU 1000000UL

/*LCD PORT*/
#define LCD_PORT PORTA

/* Control Pins */
#define LCD_RS PIN1
#define LCD_RW PIN2
#define LCD_ENABLE PIN3


/*define 4-bit Mode Or 8-bit Mode*/

#define Bit_Mode4
//#define bit_Mode8

/*Least Data Lines*/
#ifdef bit_Mode8

#define LCD_0 0
#define LCD_1 0
#define LCD_2 0
#define LCD_3 0

#endif

#ifdef Bit_Mode4

/* Most Data Lines */
#define LCD_D4 PIN4
#define LCD_D5 PIN5
#define LCD_D6 PIN6
#define LCD_D7 PIN7

/* Commands For LCD_Send_CMd */
#define Function_Set_4Bit 0x28
#define Clear_Command 0x01
#define LCD_CMD_INIT2_4_BIT 0x32
#define LCD_CMD_INIT1_4_BIT	0x33
#define Cyrser_On 0x0E
#define LCD_CMD_1ST_LINE 0x80
#define LCD_CMD_2ND_LINE 0xC0
#define LCD_CMD_INCREMNT_CURSER 0x06

#endif

#endif /* LCD_CFG_H_ */