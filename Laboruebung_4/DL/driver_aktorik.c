#include "driver_aktorik.h"
#include <msp430.h>

extern volatile uint32_t counter_A1_CCR0;

// Steering ******************************

void Driver_SetSteering(int8_t value)
{
    // value == -100 => 100% left
    // value == 0    => centered
    // value == 100  => 100% right

    if (value > 100) value = 100;
    if (value < -100) value = -100;

    TA1CCR2 = (STEERING_CENTER + 10 * value);
}

void Driver_SteeringInit(void)
{
    Driver_SetSteering(0);
}

// Throttle ******************************

void Driver_SetThrottle(int8_t value)
{

}

void Driver_ThrottleInit(void)
{
    counter_A1_CCR0 = 0;
    TA1CCTL0 |= CCIE;            // Timer_A1: CCR0 Capture/Compare interrupt enable
    while (1 == 1)
    {
        if (counter_A1_CCR0 > 3) break;
    }
    counter_A1_CCR0 = 0;

    TA1CCTL0 &= ~CCIE;            // Timer_A1: CCR0 Capture/Compare interrupt disable
    // TA1CCR1 = 0x01F4;   // 500us
}
