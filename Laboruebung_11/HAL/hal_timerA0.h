#ifndef _HAL_TIMERA0_H_
#define _HAL_TIMERA0_H_

#include <msp430.h>
#include <stdint.h>

#define PERIOD_10HZ 62500      // 2,5MHz / 10 Hz / 4 => 62500

void HAL_TimerA0_Init(void);

#endif
