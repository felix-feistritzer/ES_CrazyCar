#include "al_test.h"
#include "al_algorithm.h"
#include "driver_aktorik.h"
#include "driver_sensor.h"
#include "hal_adc12.h"
#include "hal_timerA0.h"

extern ADC12Com adcCom;
extern uint16_t ticks_cnt;
extern uint16_t rpm_speed;

DriveState_Test_t DState_Test;

extern uint16_t distance;
extern int16_t sen_diff_old;
extern int16_t sen_diff;
extern int16_t sen_diff_delta;

extern const float kp;
extern const float kd;

extern const uint8_t time_delta_inv;

void AL_Algorithm_Test(void)
{
    distance = ticks_cnt * 5; // Distance in mm

    sen_diff_old = sen_diff;
    sen_diff = Driver_GetRightDist() - Driver_GetLeftDist();
    sen_diff_delta = sen_diff - sen_diff_old;


    switch (DState_Test)
    {
        case INIT_T:
            ticks_cnt = 0;
            DState_Test = START_T;
            break;
        case START_T:
            Driver_SetThrottle(100);
            Driver_SetSteering(0);
            if (Driver_GetFrontDist() < 1400)
            {
                if (rpm_speed > 1000)
                {
                    Driver_SetThrottle(-70);
                }
                else if (rpm_speed > 500)
                {
                    Driver_SetThrottle(-40);
                }
                else
                {
                    DState_Test = STOP_T;
                }
            }
            break;
        case STOP_T:
            Driver_SetThrottle(0);
            break;
    }
}
