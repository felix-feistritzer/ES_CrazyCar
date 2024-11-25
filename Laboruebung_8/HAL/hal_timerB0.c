#include "hal_timerB0.h"
#include "hal_gpio.h"

void HAL_TimerB0_Init(void)
{

    // TB0CTL
    TB0CTL |= TACLR;            // Timer_B0 clear
    TB0CTL &= ~TBSSEL_3;
    TB0CTL |= TBSSEL__SMCLK;    // Timer_B0 clock source set to SMCLK

    // Divider
    TB0CTL &= ~ID_3;            // Input divider set to /1
    TB0EX0 &= ~TBIDEX_7;        // Input divider set to /1

    // TB0CCTL0 => 120Hz
    TB0CCTL0 &= ~CCIFG;         // Clear interrupt flags
    TB0CCTL0 &= ~COV;           // Capture overflow: no capture overflow occurred
    TB0CCTL0 &= ~CAP;           // Capture mode: Compare mode
    TB0CCTL0 &= ~CM_3;
    TB0CCTL0 |= CM_1;           // Capture mode: Capture on rising edge

    // TB0CCTL1 => SAMPCON
    TB0CCTL1 &= ~CCIFG;         // Clear interrupt flag
    TB0CCTL1 &= ~COV;           // Capture overflow: now capture overflow occurred
    TB0CCTL1 |= CM_1;           // Capture mode: on rising edge
    TB0CCTL1 &= ~CAP;           // Compare mode
    TB0CCTL1 |= OUTMOD_7;       // Output mode: Reset/Set

    TB0CCR0 |= 20833;           // 2.5 MHz /20833 => 120Hz
    TB0CCR1 |= 1;               // SAMPCON: short impuls

    TB0CTL |= MC__UP;           // Mode control set to Up mode
}
