/*
 * DIO_Registers.h
 *
 * Created: 2/13/2019 2:56:54 PM
 *  Author: AVE-LAP-040
 */ 


#ifndef DIO_REGISTERS_H_
#define DIO_REGISTERS_H_

#define INPUT 0
#define OUTPUT 1
#define LOW 0
#define HIGH 1

#define PINA (*(volatile uint8*)0x39)
#define PINB (*(volatile uint8*)0x36)
#define PINC (*(volatile uint8*)0x33)
#define PIND (*(volatile uint8*)0x30)

#define DDRA (*(volatile uint8*)0x3A)
#define DDRB (*(volatile uint8*)0x37)
#define DDRC (*(volatile uint8*)0x34)
#define DDRD (*(volatile uint8*)0x31)

#define PORTA (*(volatile uint8*)0x3B)
#define PORTB (*(volatile uint8*)0x38)
#define PORTC (*(volatile uint8*)0x35)
#define PORTD (*(volatile uint8*)0x32)





#endif /* DIO_REGISTERS_H_ */