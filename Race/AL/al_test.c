#include "al_test.h"
#include "al_algorithm.h"
#include "driver_aktorik.h"
#include "driver_sensor.h"
#include "hal_adc12.h"
#include "hal_timerA0.h"
#include "driver_lcd.h"

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

int16_t throttle_integral;

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
            throttle_integral = 0;
            DState_Test = START_T;
            break;
        case START_T:
            Driver_SetSteering(AL_Regler_Test());
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed_Test(1000);
            }
            else
            {
                AL_SetSpeed(3000);
            }

            if (Driver_GetFrontDist() < 100)
            {
                DState_Test = STOP_T;
                ticks_cnt = 0;
            }
            break;
        case STOP_T:
            Driver_SetThrottle(0);
            break;
    }
}

int16_t AL_Regler_Test(void)
{
    const int16_t kp_test = 3277; // 0.1 * 32767
    const int16_t kd_test = 328;  // 0.01 * 32767
    const int16_t td_inv = 60;

    int32_t result;
    int32_t result_p;
    int32_t result_d;

    result_p = (int32_t)sen_diff * kp_test;

    result_d = (int32_t)sen_diff_delta * td_inv;
    result_d = (int32_t)result_d * kd_test;

    result = result_p + result_d;
    result = result >> 15;

    return (int16_t)result;
}

void AL_SetSpeed_Test(int16_t target_speed)
{
    const int16_t dt = 546;  // (1 / 60) * 32767
    const int16_t throttle_kp = 6553; // 0.2 * 32767
    const int16_t throttle_ki = 1638; // 0.05 * 32767

    int32_t throttle;
    int32_t throttle_p;
    int32_t throttle_i;
    int16_t speed_diff;
    int32_t speed_diff_i;

    speed_diff = target_speed - rpm_speed;

    if (speed_diff < -500)
    {
        throttle = -10;
    }
    else
    {
        throttle_p = (int32_t)speed_diff * throttle_kp;

        speed_diff_i = (int32_t)speed_diff * dt;
        speed_diff_i = speed_diff_i >> 15;

        throttle_integral = throttle_integral + speed_diff_i;

        throttle_i = (int32_t)throttle_integral * throttle_ki;

        throttle = throttle_p + throttle_i;
        throttle = throttle >> 15;

        if (throttle > 100)
        {
            throttle = 70;
            throttle_integral = throttle_integral - speed_diff_i;
        }
        else if (throttle < 30)
        {
            throttle = 30;
            throttle_integral = throttle_integral - speed_diff_i;
        }
    }

    Driver_SetThrottle((int16_t)throttle);
}
