/*
 * DIO_Registers_Definitions.h
 *
 * Created: 2/13/2019 3:19:17 PM
 *  Author: AVE-LAP-040
 */ 

/* 

*/
#ifndef DIO_REGISTERS_DEFINITIONS_H_
#define DIO_REGISTERS_DEFINITIONS_H_



#define INPUT 0
#define OUTPUT 1

/*PORTS Macros*/
#define PORTA_R 1
#define PORTB_R 2
#define PORTC_R 3
#define PORTD_R 4

/*PORTA PINS*/
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
/*PORTB PINS*/
#define PIN8 8
#define PIN9 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15
/*PORTC*/
#define PIN16 16
#define PIN17 17
#define PIN18 18
#define PIN19 19
#define PIN20 20
#define PIN21 21
#define PIN22 22
#define PIN23 23
/*PORTD*/
#define PIN24 24
#define PIN25 25
#define PIN26 26
#define PIN27 27
#define PIN28 28
#define PIN29 29
#define PIN30 30
#define PIN31 31

/*To Set Direction For Specific Pin*/
void DIO_SetPinDirection(uint8 PinNum,uint8 PinDirection);
/*To Write To a Specific Pin*/
void DIO_WritePin(uint8 PinNum,uint8 PinValue);
/*To read From Specific Pin*/
uint8 DIO_ReadPin(uint8 PinNum);
uint8 DIO_TogglePin(uint8 PinNum);
/*For Reading From Port 8-Bit
*write PORTA_R for Port A
*write PORTB_R for Port B
*write PORTC_R for Port c
*write PORTD_R for Port D
*write PORTE_R for
*/
uint8 DIO_ReadPort(uint8 PortNumber);
/*For writing to port 8-bit*/
uint8 DIO_WritePort(uint8 PortNumber);



#endif /* DIO_REGISTERS_DEFINITIONS_H_ */