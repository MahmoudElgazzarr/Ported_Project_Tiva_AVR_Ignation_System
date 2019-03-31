/*
 * UART.c
 *
 * Created: 3/11/2019 3:51:46 PM
 *  Author: AVE-LAP-040
 */ 

#define F_CPU 16000000UL

#include "Types.h"
#include <stdint.h>
#include "UART.h"
#include "UART_CFG.h"
#include "BitwiseOperation.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

UART_Config UART_Config_S;
/**/
volatile uint8 UART_Flag = 0 ;
volatile uint8 DataToSend = 0 ;
extern QueueHandle_t xUartRecv ;

#define UART_PERIODICITY 10

void UART0_init (void)
{
	uint32 UBRR_temp;
	
	/*Temp uint8 to save UCSRC Data because you can't save data direct in it*/
	volatile uint8 UCSRC_REG_TEMP = 0;
	

	/* Clear URSEL Bit to Write in UBRRH Register */
	Clear_Bit(UBRRH_REG,URSEL);
	
	UBRR_temp = (FOSC / (SIXTEEN * UART_Config_S.BaudRate)) - ONE  ;

	/* Set Bits (11,10,9,8) in BaudRate to UBRRH Register */
	UBRRH_REG = (uint8)( UBRR_temp >> EIGHT_BITS );
	UBRRL_REG = (uint8)(UBRR_temp); /* Set First Eight Bits in BaudRate to UBRRL Register */
	
	/* Set URSEL Bit to Write in UCSRC Register */
	Set_Bit(UCSRC_REG_TEMP,URSEL);
	
	/* Set UART Clock Polarity*/
	switch(UART_Config_S.ClockPolarity)
	{
		case UART_RisingPol  : Clear_Bit(UCSRC_REG_TEMP,UCPOL); /* Rising Edge */
		UCSRC_REG |= UCSRC_REG_TEMP;
		break;
		case UART_FallingPol : Set_Bit(UCSRC_REG_TEMP,UCPOL); /* Falling Edge */
		UCSRC_REG |= UCSRC_REG_TEMP;
		break;
		default:break;
	}
	
	/* Set Data Size ( 5 bit, 6 bit, 7 bit, 8 bit ) */
	switch(UART_Config_S.DataSize)
	{
		case UART_5_Bits :  Clear_Bit(UCSRC_REG_TEMP,UCSZ0); /* Clear UCSZ0 BIT and Clear UCSZ1  */
		Clear_Bit(UCSRC_REG_TEMP,UCSZ1); /* Data Size 5 Bits */
		UCSRC_REG |= UCSRC_REG_TEMP;
		break;
		case UART_6_Bits :  Set_Bit(UCSRC_REG_TEMP,UCSZ0);   /* Set UCSZ0 BIT and Clear UCSZ1  */
		Clear_Bit(UCSRC_REG_TEMP,UCSZ1); /* Data Size 6 Bits */
		UCSRC_REG |= UCSRC_REG_TEMP;
		break;
		case UART_7_Bits :  Clear_Bit(UCSRC_REG_TEMP,UCSZ0); /* Clear UCSZ0 BIT and Set UCSZ1  */
		Set_Bit(UCSRC_REG_TEMP,UCSZ1);   /* Data Size 7 Bits */
		UCSRC_REG |= UCSRC_REG_TEMP;
		break;
		case UART_8_Bits :  Set_Bit(UCSRC_REG_TEMP,UCSZ0);  /* Set UCSZ0 BIT and Set UCSZ1  */
		Set_Bit(UCSRC_REG_TEMP,UCSZ1);  /* Data Size 8 Bits */
		UCSRC_REG |= UCSRC_REG_TEMP;
		break;
		default:break;
		
	}
	
	
	/* Set Numbers of Stop Bits ( 1 or 2) */
	switch(UART_Config_S.No_StopBits)
	{
		case UART_OneStopBit : Clear_Bit(UCSRC_REG_TEMP,USBS); /* Clear USBS Bit for one stop bit */
		UCSRC_REG |= UCSRC_REG_TEMP;
		break;
		case UART_TwoStopBit : Set_Bit(UCSRC_REG_TEMP,USBS);   /* Set USBS Bit for two stop bit */
		UCSRC_REG |= UCSRC_REG_TEMP;
		break;
		default:break;
	}
	
	/* Set Parity Mode (No Parity , Even , Odd) */
	switch (UART_Config_S.ParityMode)
	{
		case UART_DisableParityBit : Clear_Bit(UCSRC_REG_TEMP,UPM0); /* Clear UPM0_BIT and Clear UPM1 BIT for Disable Parity Bit */
		Clear_Bit(UCSRC_REG_TEMP,UPM1);
		UCSRC_REG |= UCSRC_REG_TEMP;
		break;
		case UART_EvenParityBit    : Clear_Bit(UCSRC_REG_TEMP,UPM0); /* Clear UPM0_BIT and Set UPM1 BIT for Disable Parity Bit */
		Set_Bit(UCSRC_REG_TEMP,UPM1);
		UCSRC_REG |= UCSRC_REG_TEMP;
		break;
		case UART_OddParityBit     : Set_Bit(UCSRC_REG_TEMP,UPM0);   /* Set UPM0_BIT and Set UPM1 BIT for Disable Parity Bit */
		Set_Bit(UCSRC_REG_TEMP,UPM1);
		UCSRC_REG |= UCSRC_REG_TEMP;
		break;
		default:break;
	}
	
	/* Set Speed Mode ( Normal or Double ) */
	switch(UART_Config_S.SpeedMode)
	{
		case UART_NormalSpeedMode : Clear_Bit(UCSRA_REG,U2X); /* Clear U2X Bit for Normal Speed Mode */
		break;
		case UART_DoubleSpeedMode : Set_Bit(UCSRA_REG,U2X);  /* Set U2X Bit for Double Speed Mode */
		break;
		default:break;
	}
	
	/* Enable receiver and transmitter*/
	
	Set_Bit(UCSRB_REG,TXEN);  /* Set TXEN  Bit For Enable Transmitter */
	Set_Bit(UCSRB_REG,RXEN);  /* Set RXEN  Bit For Enable Receiver */
	Set_Bit(UCSRB_REG,RXCIE); /* Set RXCIE Bit For Enable Interrupt Receiver */
	
}


void UART0_Send( uint8 data )
{
	/* Wait for empty transmit buffer */
	while ( !(UCSRA_REG & (1<<UDRE) ) );
	
	/* Put data into buffer, sends the data */
	UDR_REG = data;
}
uint8 UART0_Recv( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA_REG & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR_REG;
}

void UartRecv_Task(void *pvParameters)
{

	vTaskDelay(500);
	while(1)
	{
		uint8 data = 0 ;

		if(UCSRA_REG & (1<<RXC))
		{   data = UART0_Recv();
			xQueueSendToBack(xUartRecv, &data , 10 );

		}
		vTaskDelay(UART_PERIODICITY);
	}
}
