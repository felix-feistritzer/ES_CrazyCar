#include "hal_timerA0.h"
#include "hal_gpio.h"
#include "driver_lcd.h"

volatile uint16_t rpm_ticks = 0;
volatile uint16_t rpm_speed = 0;
volatile uint16_t rpm_speed_old = 0;

void HAL_TimerA0_Init(void)
{
    TA0CTL |= TACLR;            // Timer_A clear
    TA0CTL |= TASSEL__SMCLK;    // clock source: Sub-Master CLK

    // CCTL0 Period
    TA0CCTL0 &= ~CCIFG;         // Clear interrupt flag
    TA0CCTL0 &= ~COV;           // Capture overflow: now capture overflow occurred
    TA0CCTL0 &= ~CAP;           // Compare mode
    TA0CCTL0 |= ID__8;          // Input divider / 8
    TA0CCTL0 |= CCIE;           // Interrupt enable


    // CCTL2 RPM_SENSOR
    TA0CCTL2 &= ~CCIFG;         // Clear interrupt flag
    TA0CCTL2 &= ~COV;           // Capture overflow: now capture overflow occurred
    TA0CCTL2 |= CM_3;           // Capture mode: on rising and falling edge
    TA0CCTL2 |= CAP;            // Capture mode
    TA0CCTL2 |= CCIE;           // Interrupt enable

    TA0CCR0 = PERIOD_10HZ;      // 2,5MHz / 10 Hz / 8 => 31250

    TA0CTL |= MC__UP;           // Mode control set to Up Mode
}

// Interrupts
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TimerA0_0(void)
{
    rpm_speed = (rpm_ticks * 5) * 10; // (Ticks * 5mm) * 10Hz
    rpm_speed = (rpm_speed + rpm_speed_old) >> 1;
    rpm_speed_old = rpm_speed;
    rpm_ticks = 0;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TimerA0_1(void)
{
    rpm_ticks++;
    TA0CCTL2 &= ~CCIFG;     // clear interrupt flag
}

