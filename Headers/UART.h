/*
 * UART.h
 *
 * Created: 2/27/2019 1:11:51 PM
 *  Author: AVE-LAP-040
 */ 




#ifndef UART_H_
#define UART_H_
#include "Types.h"

#define UBRRL_REG (*(volatile uint8*) 0x29)
#define UCSRB_REG (*(volatile uint8*) 0x2A)
#define UCSRA_REG (*(volatile uint8*) 0x2B)
#define UDR_REG (*(volatile uint8*) 0x2C)
#define SREG_REG (*(volatile uint8*)0x5F)
#define UBRRH_REG (*(volatile uint8*)0x40)
#define UCSRC_REG (*(volatile uint8*)0x40)

#define SIXTEEN         ((uint8) 16 )
#define ONE             ((uint8) 1 )
#define EIGHT_BITS      ((uint8)8)
#define SIXTEEN_BITS    ((uint8)16)
#define FIRST_FOUR_BITS ((uint8) 0x0F)


void UART0_init (void);
uint8 UART0_Recv( void );
void UART0_Send( uint8 data );
void UartRecv_Task(void *pvParameters);

enum UBRRH_BITS_e{
	URSEL = ((uint8) 7 ),
};


enum UCSRC_BITS_e{
	UCPOL = ((uint8) 0 ),
	UCSZ0 = ((uint8) 1 ),
	UCSZ1 = ((uint8) 2 ),
	USBS  = ((uint8) 3 ),
	UPM0  = ((uint8) 4 ),
	UPM1  = ((uint8) 5 ),
	UMSEL = ((uint8) 6 ),
};

enum UCSRA_BITS_e{
	MPCM = ((uint8) 0 ),
	U2X  = ((uint8) 1 ),
	PE   = ((uint8) 2 ),
	DOR  = ((uint8) 3 ),
	FE   = ((uint8) 4 ),
	UDRE = ((uint8) 5 ),
	TXC  = ((uint8) 6 ),
	RXC  = ((uint8) 7 ),
};

enum UCSRB_BITS_e{
	TXB8  = ((uint8) 0 ),
	RXB8  = ((uint8) 1 ),
	UCSZ2 = ((uint8) 2 ),
	TXEN  = ((uint8) 3 ),
	RXEN  = ((uint8) 4 ),
	UDRIE = ((uint8) 5 ),
	TXCIE = ((uint8) 6 ),
	RXCIE = ((uint8) 7 ),
};

#endif /* UART_H_ */