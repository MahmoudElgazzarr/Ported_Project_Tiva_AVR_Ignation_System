

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "FSM.h"
#include "Buttons.h"
#include "Manager.h"
#include "Spi.h"
#include "UART.h"

typedef enum{
    IgnitionOff,
    MaintainSpeed,
    IncreaseSpeed,
    DecreaseSpeed,
    Brake,
    FireAirbag,
    SystemOn
}CarState_e;

extern EventGroupHandle_t xBtnEventGroup;

/*******************************************************************/
/* AlignData                                                       */
/* Parameters : uint8,uint8                                        */
/* I/p : command , dist                                            */
/* O/p : uint8                                                     */
/* Return : alligned data                                          */
/* fn that allign distance and cmd into 1byte                      */
/*******************************************************************/
uint8_t AlignData(uint8_t Cmd , uint8_t Dist)
{
    double Distance = Dist/8.5;
    uint8_t u8Distance = (uint8_t)(Distance);
    uint8_t data = 0 ;
    data = Cmd ;
    data = data << 5 ;
    data |= u8Distance ;
    return data;
}

/*******************************************************************/
/* FSM_Handler_Task                                                */
/* Parameters :                                                    */
/* I/p : *pvParameter                                              */
/* O/p : N/A                                                       */
/* Return : void                                                   */
/* Task that checks sensor data and send action on SPI             */
/*******************************************************************/
void FSM_Handler_Task(void *pvParameters)
{

    uint8_t IgnitionFlag = 0 ;
    static uint8_t CurrentState = IgnitionOff;
    EventBits_t uxBits;
    const TickType_t xTicksToWait = 100 / portTICK_PERIOD_MS;
    uint8_t Distance = 0 ;


    while(1)
    {

        //UARTCharPut(UART0_BASE, 'A');

    /* Get Distance */
    Distance = Get_Distance();
    /* Check for DistEventFlag */
    uxBits = xEventGroupWaitBits(
                              xBtnEventGroup,   /* The event group being tested. */
                              DISTANCE_FLAG | BTN1_FLAG, /* The bits within the event group to wait for. */
                              pdTRUE,        /* BIT_0 & BIT_4 should be cleared before returning. */
                              pdFALSE,       /* Don't wait for both bits, either bit will do. */
                              xTicksToWait );/* Wait a maximum of 100ms for either bit to be set. */


    /* Check for event flag ( Btn==1 for 1sec)*/
    if( ( ( uxBits &BTN1_FLAG ) != 0) && (CurrentState == IgnitionOff) )
    {
        IgnitionFlag = 1 ;

        if( (Distance >= 0) && (Distance <= 5) )
        {
            CurrentState = SystemOn;
            SPI0_Send(AlignData(CurrentState,0));
        }
        else if( (Distance > 5) && (Distance <= 20) )
        {
            CurrentState = Brake;
            SPI0_Send(AlignData(CurrentState,Distance));
        }
        else if( (Distance > 20) && (Distance <= 90) )
        {
            CurrentState = DecreaseSpeed ;
            SPI0_Send(AlignData(CurrentState,Distance));
        }
        else if( (Distance > 90) && (Distance <= 160) )
        {
            CurrentState = MaintainSpeed ;
            SPI0_Send(AlignData(CurrentState,Distance));
        }
        else if( (Distance > 160) && (Distance <= 255) )
        {
            CurrentState = IncreaseSpeed ;
            SPI0_Send(AlignData(CurrentState,Distance));
        }
    }

    /* If Btn already Pressed */
    if(IgnitionFlag == 1)
    {
        /* If Distance Sent */
        if( ( uxBits & DISTANCE_FLAG ) != 0)
        {
            if( (Distance >= 0) && (Distance <= 5) )
            {
                CurrentState = FireAirbag;
                SPI0_Send(AlignData(CurrentState,Distance));
            }
            else if( (Distance > 5) && (Distance <= 20) )
            {
                CurrentState = Brake;
                SPI0_Send(AlignData(CurrentState,Distance));
            }
            else if( (Distance > 20) && (Distance <= 90) )
            {
                CurrentState = DecreaseSpeed ;
                SPI0_Send(AlignData(CurrentState,Distance));
            }
            else if( (Distance > 90) && (Distance <= 160) )
            {
                CurrentState = MaintainSpeed ;
                SPI0_Send(AlignData(CurrentState,Distance));
            }
            else if( (Distance > 160) && (Distance <= 255) )
            {
                CurrentState = IncreaseSpeed ;
                SPI0_Send(AlignData(CurrentState,Distance));
            }
        }
        else
        {
        }
    }
    vTaskDelay(50);
}
}

