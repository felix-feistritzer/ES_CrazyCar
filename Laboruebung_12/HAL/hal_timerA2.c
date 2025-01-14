#include "hal_timerA2.h"
#include "hal_gpio.h"

volatile uint8_t A2_Flag;

void HAL_TimerA2_Init(void)
{
    TA2CTL |= TACLR;            // Timer_A clear
    TA2CTL |= TASSEL__SMCLK;    // clock source: Sub-Master CLK

    // CCTL0
    TA2CCTL0 &= ~CCIFG;         // Clear interrupt flag
    TA2CCTL0 &= ~COV;           // Capture overflow: now capture overflow occurred
    TA2CCTL0 |= CM_1;           // Capture mode: on rising edge
    TA2CCTL0 &= ~CAP;           // Compare mode

    TA2CCR0 |= A2_60HZ;         // 2,5MHz / 60Hz => 41666,67

    TA2CTL |= MC__UP;           // Mode control set to Up mode

    A2_Flag = 0;
}

void HAL_TimerA2_Start(void)
{
    TA2CCTL0 |= CCIE;           // Timer_A2: CCR0 Capture/Compare interrupt enable
}

void HAL_TimerA2_Stop(void)
{
    TA2CCTL0 &= ~CCIE;          // Timer_A2: CCR0 Capture/Compare interrupt disable
}

// Interrupts
#pragma vector = TIMER2_A0_VECTOR
__interrupt void TimerA2(void)
{
    A2_Flag = 1;
}
