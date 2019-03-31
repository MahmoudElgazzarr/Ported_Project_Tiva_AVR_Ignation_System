/*
 * Buttons.c
 *
 * Created: 2/25/2019 2:25:30 PM
 *  Author: AVE-LAP-040
 */ 

#include <stdint.h>
#include "Types.h"
#include "DIO.h"
#include "DIO_Definitions.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "Buttons.h"

extern EventGroupHandle_t xBtnEventGroup;


/* Btns_Init                                                       */
/* Parameters : N/A                                                */
/* I/p : N/A                                                       */
/* O/p : N/A                                                       */
/* Return : void                                                   */
/* Function that init btns*/
void Btns_Init(void)
{
	
}
uint8 Btn1_Read()
{
	uint8 return_value = DIO_ReadPin(Button1);
	return return_value;
}

void Btn1_Task(void *pvParameters)
{
	uint8_t Btn1_State=0 ;
	static uint16_t Counter = 0 ;
	while(1)
	{
		/* Read BTN1 */
		Btn1_State = Btn1_Read();
		if(Btn1_State)
		{
			Counter ++ ;
		}
		else
		{
			Counter = 0 ;
		}
		if(Counter > 1000 )
		{
			xEventGroupSetBits(xBtnEventGroup, BTN1_FLAG);
			vTaskSuspend(NULL);
		}
		vTaskDelay(1);
	}
}
