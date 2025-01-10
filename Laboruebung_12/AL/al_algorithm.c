#include "al_algorithm.h"
#include "driver_aktorik.h"

uint8_t cnt = 0;

void AL_Algorithm(void)
{
    Driver_SetThrottle(40);

    if (cnt == 0)
    {
        Driver_SetSteering(50);
        cnt++;
    }
    else
    {
        Driver_SetSteering(-50);
        cnt = 0;
    }


}
