#include "hal_timerB0.h"
#include "hal_gpio.h"

void HAL_TimerB0_Init(void)
{

    TB0CTL &= ~TBSSEL_3;
    TB0CTL |= TBSSEL__SMCLK;    // Timer_B clock source set to SMCLK

    TB0CTL &= ~ID_3;
    TB0CTL |= ID__8;            // Input divider set to /8

    TB0EX0 &= ~TBIDEX_7;
    TB0EX0 |= TBIDEX__4;        // Input divider expansion set to /4

    TB0CCTL0 &= ~CCIFG;         // Clear interrupt flags
    TB0CCTL0 &= ~COV;           // Capture overflow: no capture overflow occurred
    TB0CCTL0 |= CCIE;           // Capture/Compare interrupt enabled
    TB0CCTL0 &= ~CAP;           // Capture mode: Compare mode

    TB0CCTL0 &= ~CM_3;
    TB0CCTL0 |= CM_1;           // Capture mode: Capture on rising edge

    TB0CCR0 &= ~0xFFFF;
    TB0CCR0 |= 0x4C4B;          // 2.5 GHz /2 /32 => 2Hz

    TB0CTL |= MC__UP;           // Mode control set to Up mode
}

// Interrupts
#pragma vector = TIMER0_B0_VECTOR
__interrupt void TimerB0(void)
{
     LCD_BL_TOGGLE;          // Toggle LCD_BL

     TB0CCTL0 &= ~CCIFG;     // Clear interrupt flag
}
