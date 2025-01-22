#include "driver_aktorik.h"
#include <msp430.h>

extern volatile uint32_t counter_A1_CCR0;

// Steering ******************************

void Driver_SetSteering(int16_t value)
{
    // value == -100 => 100% left
    // value == 0    => centered
    // value == 100  => 100% right

    if (value > 100) value = 100;
    if (value < -100) value = -100;

    TA1CCR2 = (STEERING_CENTER - STEERING_OFFSET + 10 * value);
}

void Driver_SteeringInit(void)
{
    Driver_SetSteering(0);
}

// Throttle ******************************

void Driver_SetThrottle(int16_t value)
{
    // value == -100 => Max RPW
    // value == 0    => Max Break
    // value == 100  => Max FPW

    if (value > 100) value = 100;
    if (value < -100) value = -100;

    if (value > 0)
    {
        TA1CCR1 = THROTTLE_MINFPW + 25 * value;
    }
    else if (value < 0)
    {
        TA1CCR1 = THROTTLE_MINRPW + 25 * value;
    }
    else // value == 0
    {
        TA1CCR1 = THROTTLE_MAXBREAK;
    }

}

void Driver_ThrottleInit(void)
{
    TA1CCTL0 |= CCIE;            // Timer_A1: CCR0 Capture/Compare interrupt enable

    pwmCycles(THROTTLE_MAXRPW, 131);
    pwmCycles(THROTTLE_MINRPW, 128);
    pwmCycles(THROTTLE_MINFPW, 128);
    pwmCycles(THROTTLE_MAXFPW, 128);
    pwmCycles(THROTTLE_MAXBREAK, 30);

    TA1CCTL0 &= ~CCIE;            // Timer_A1: CCR0 Capture/Compare interrupt disable
}

void pwmCycles(uint16_t pwm, uint16_t cycles)
{
    counter_A1_CCR0 = 0;
    TA1CCR1 = pwm;

    while (counter_A1_CCR0 <= cycles)
    {

    }
}
