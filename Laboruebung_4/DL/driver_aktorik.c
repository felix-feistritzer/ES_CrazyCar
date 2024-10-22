#include "driver_aktorik.h"
#include <msp430.h>

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
