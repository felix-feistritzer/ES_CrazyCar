#include "hal_timerB0.h"
#include "hal_gpio.h"

void HAL_TimerB0_Init(void)
{
    TB0CTL |= TBSSEL__SMCLK;    // Timer_B clock source set to SMCLK
    TB0CTL |= ID__8;            // Input divider set to /8
    TB0EX0 |= TBIDEX__4;        // Input divider expansion set to /4
    TB0CTL |= MC__UP;           // Mode control set to Up mode
    TB0CTL |= TBIE;             // Timer_B interrupt enable

    TB0CCR0 |= 0x9896;           // 2.5 GHz /2 /32 => 2Hz

    TB0CCTL0 |= CM_1;            // Capture mode: Capture on rising edge
    TB0CCTL0 &= ~CAP;            // Capture mode: Compare mode
    TB0CCTL0 |= CCIE;            // Capture/Compare interrupt enabled

    TB0CCTL0 &= ~CCIFG;          // Clear interrupt flags
    TB0CTL &= ~TBIFG;
}

// Interrupts
#pragma vector = TIMER0_B0_VECTOR
__interrupt void TimerB0(void)
{

     LCD_BL_TOGGLE;          // Toggle LCD_BL

     TB0CCTL0 &= ~CCIFG;     // Clear interrupt flag
     TB0CTL &= ~TBIFG;
}
