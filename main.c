

#include "Types.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "FSM.h"
#include "UART.h"
#include "Buttons.h"
#include "Spi.h"


QueueHandle_t xUartRecv ;
EventGroupHandle_t xBtnEventGroup;

/*****************************************************************************/
/*****************************************************************************/
/**This hook is called by FreeRTOS when an stack overflow error is detected.**/
/*****************************************************************************/
/*****************************************************************************/
void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    /*
     This function can not return, so loop forever.  Interrupts are disabled
     on entry to this function, so no processor interrupts will interrupt
     this loop.
    */
    while(1)
    {
    }
}

int main(void)
{


    Btns_Init();
    UART0_init();
    SPI0_Master_Init();
    /* The queue was created. */
    xUartRecv = xQueueCreate(10,sizeof(uint8_t));

    /* Attempt to create the event group. */
    xBtnEventGroup = xEventGroupCreate();

    /* Create Tasks */
    //xTaskCreate(TaskInit,"Init_Task",60,NULL,4,NULL);
    xTaskCreate(Btn1_Task,"Btn1_Task",60,NULL,2,NULL);
    xTaskCreate(UartRecv_Task,"Uart_Task",60,NULL,2,NULL);
    xTaskCreate(FSM_Handler_Task,"FSM",60,NULL,2,NULL);

    /* Start Schedular */
    vTaskStartScheduler();

    while(1)
        {
            //SPI0_Send('A');
        }
}
