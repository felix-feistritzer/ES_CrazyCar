#include "hal_timerA1.h"
#include "hal_gpio.h"
#include "al_general.h"
#include "al_algorithm.h"

extern State_t CCState;

void HAL_TimerA1_Init(void)
{
    TA1CTL |= TACLR;            // Timer_A clear
    TA1CTL |= TASSEL__SMCLK;    // clock source: Sub-Master CLK

    // CCTL0 => Period
    TA1CCTL0 &= ~CCIFG;         // Clear interrupt flag
    TA1CCTL0 &= ~COV;           // Capture overflow: now capture overflow occurred
    TA1CCTL0 |= CM_1;            // Capture mode: on rising edge
    TA1CCTL0 &= ~CAP;            // Compare mode
    // TA1CCTL0 |= OUTMOD_7;        // Output mode: Reset/Set
    // TA1CCTL0 |= CCIE;            // Capture/Compare interrupt enable

    // CCTL1 => Throttle
    TA1CCTL1 &= ~CCIFG;         // Clear interrupt flag
    TA1CCTL1 &= ~COV;           // Capture overflow: now capture overflow occurred
    TA1CCTL1 |= CM_1;            // Capture mode: on rising edge
    TA1CCTL1 &= ~CAP;            // Compare mode
    TA1CCTL1 |= OUTMOD_7;        // Output mode: Reset/Set
    // TA1CCTL1 |= CCIE;            // Capture/Compare interrupt enable

    // CTL2 => Steering
    TA1CCTL2 &= ~CCIFG;         // Clear interrupt flag
    TA1CCTL2 &= ~COV;           // Capture overflow: now capture overflow occurred
    TA1CCTL2 |= CM_1;            // Capture mode: on rising edge
    TA1CCTL2 &= ~CAP;            // Compare mode
    TA1CCTL2 |= OUTMOD_7;        // Output mode: Reset/Set
    // TA1CCTL2 |= CCIE;            // Capture/Compare interrupt enable

    TA1CCR0 |= PWM_60HZ;        // 2,5MHz / 60Hz => 41666,67
    TA1CCR1 |= 0x0;             // Throttle duty cycle => 0%
    TA1CCR2 |= 0x0;             // Steering duty cycle => 0%

    TA1CTL |= MC__UP;           // Mode control set to Up mode
}

// Interrupts
#pragma vector = TIMER1_A0_VECTOR
__interrupt void TimerA1(void)
{
    if (CCState == Start || CCState == CCW || CCState == CW)
    {
        AL_Algorithm();
    }
    else
    {
        counter_A1_CCR0++;
    }
}
