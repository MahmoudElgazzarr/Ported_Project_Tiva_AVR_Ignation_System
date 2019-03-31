/*
 * Buttons.h
 *
 * Created: 2/25/2019 2:24:47 PM
 *  Author: AVE-LAP-040
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "Types.h"

#define Button1 PIN10
#define BTN1_FLAG   (1 << 1)

void Btns_Init(void);
uint8 Btn1_Read();
void Btn1_Task(void *pvParameters);


#endif /* BUTTONS_H_ */