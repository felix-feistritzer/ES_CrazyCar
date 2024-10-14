#include "hal_timerB0.h"

void HAL_TimerB0_Init(void)
{
    TB0CTL |= TBSSEL__SMCLK;    // Timer_B clock source set to SMCLK
    TB0CTL |= ID__8;            // Input divider set to /8
    TB0EX0 |= TBIDEX__4;        // Input divider expansion set to /4
    TB0CCR0 = 52083;            // Timer_B capture/compare 2.5 MHz / 24
    TB0CTL |= MC__UP;           // Mode control set to Up mode


}

// Interrupts
#pragma vector = TIMER0_B0_VECTOR
__interrupt void TimerB0(void)
{

}
