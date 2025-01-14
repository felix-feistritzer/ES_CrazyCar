#ifndef _HAL_TIMERA2_H_
#define _HAL_TIMERA2_H_

#include <msp430.h>
#include <stdint.h>

#define A2_60HZ 0xA2C2  // 2,5MHz / 60Hz => 41666,67

void HAL_TimerA2_Init(void);
void HAL_TimerA2_Start(void);
void HAL_TimerA2_Stop(void);

#endif
