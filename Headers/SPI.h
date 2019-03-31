/*
 * SPI.h
 *
 * Created: 3/31/2019 4:27:05 PM
 *  Author: AVE-LAP-040
 */ 


#ifndef SPI_H_
#define SPI_H_



extern void SPI0_Master_Init(void);
extern void SPI0_Send(uint8 data_to_send);
extern uint32 SPI3_Recieve(void);
extern void SpiSend_Task(void *pvParameters);

#endif /* SPI_H_ */