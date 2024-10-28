#ifndef _HAL_TIMERA1_H_
#define _HAL_TIMERA1_H_

#include <msp430.h>
#include <stdint.h>

volatile uint32_t counter_A1_CCR0;

void HAL_TimerA1_Init(void);

#endif
