#include "al_algorithm.h"
#include "driver_aktorik.h"
#include "hal_adc12.h"
#include "driver_sensor.h"
#include "hal_timerA0.h"

extern ADC12Com adcCom;
extern uint16_t ticks_cnt;
extern uint16_t rpm_speed;

DriveState_t DState;

uint16_t distance;
int16_t sen_diff_old;
int16_t sen_diff;
int16_t sen_diff_delta;

const float kp = 0.1;
const float kd = 0.005;

const uint8_t time_delta_inv = 60;

void AL_Algorithm(void)
{
    distance = ticks_cnt * 5; // Distance in mm
    sen_diff_old = sen_diff;
    sen_diff = Driver_GetRightDist() - Driver_GetLeftDist();
    sen_diff_delta = sen_diff - sen_diff_old;


    switch (DState)
    {
        case INIT:
            ticks_cnt = 0;
            DState = START;
            break;
        case START:
            Driver_SetThrottle(70);
            Driver_SetSteering(AL_Regler());
            if (Driver_GetFrontDist() < 1400)
            {
                if (rpm_speed > 1800)
                {
                    Driver_SetThrottle(-50);
                }
                else
                {
                    Driver_SetThrottle(40);
                }
            }
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 1000)
            {
                DState = T1;
                ticks_cnt = 0;
            }
            break;
        case T1:
            Driver_SetThrottle(40);
            Driver_SetSteering(-80);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1000 && distance > 150)
            {
                DState = S2;
                ticks_cnt = 0;
            }
            break;
        case S2:
            Driver_SetThrottle(50);
            Driver_SetSteering(AL_Regler());
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 1000)
            {
                DState = T2;
                ticks_cnt = 0;
            }
            break;
        case T2:
            Driver_SetThrottle(40 + (distance >> 5));
            Driver_SetSteering(-80);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1000 && distance > 150)
            {
                DState = S3;
                ticks_cnt = 0;
            }
            break;
        case S3:
            Driver_SetThrottle(50);
            Driver_SetSteering(AL_Regler());
            if (Driver_GetLeftDist() > 750 && distance > 1600)
            {
                DState = T3;
                ticks_cnt = 0;
            }
            break;
        case T3:
            Driver_SetThrottle(40);
            Driver_SetSteering(-100);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1400 && distance > 500)
            {
                DState = S4;
                ticks_cnt = 0;
            }
            break;
        case S4:
            Driver_SetThrottle(50);
            Driver_SetSteering(AL_Regler());
            if (Driver_GetRightDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 800)
            {
                DState = T4;
                ticks_cnt = 0;
            }
            break;
        case T4:
            Driver_SetThrottle(35 + (distance >> 5));
            Driver_SetSteering(100);
            if (Driver_GetRightDist() < 750 && Driver_GetFrontDist() > 1400 && distance > 500)
            {
                DState = S5;
                ticks_cnt = 0;
            }
            break;
        case S5:
            if (distance < 1800)
            {
                Driver_SetThrottle(60);
            }
            else
            {
                if (rpm_speed > 1800)
                {
                    Driver_SetThrottle(-50);
                }
                else
                {
                    Driver_SetThrottle(40);
                }
            }
            Driver_SetSteering(AL_Regler());
            if (Driver_GetRightDist() > 750 && distance > 2200)
            {
                DState = T5;
                ticks_cnt = 0;
            }
            break;
        case T5:
            Driver_SetThrottle(40);
            Driver_SetSteering(100);
            if (Driver_GetRightDist() < 750 && Driver_GetFrontDist() > 1400 && distance > 150)
            {
                DState = S6;
                ticks_cnt = 0;
            }
            break;
        case S6:
            Driver_SetThrottle(60);
            Driver_SetSteering(AL_Regler());
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 750 && distance > 400)
            {
                DState = T6;
                ticks_cnt = 0;
            }
            break;
        case T6:
            Driver_SetThrottle(40);
            Driver_SetSteering(-100);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1400 && distance > 150)
            {
                DState = S7;
                ticks_cnt = 0;
            }
            break;
        case S7:
            Driver_SetThrottle(50);
            Driver_SetSteering(AL_Regler());
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 800 && distance > 500)
            {
                DState = T7;
                ticks_cnt = 0;
            }
            break;
        case T7:
            Driver_SetThrottle(40);
            Driver_SetSteering(-80);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1400 && distance > 150)
            {
                DState = S8;
                ticks_cnt = 0;
            }
            break;
        case S8:
            Driver_SetThrottle(50);
            Driver_SetSteering(AL_Regler());
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 800 && distance > 1000)
            {
                DState = T8;
                ticks_cnt = 0;
            }
            break;
        case T8:
            Driver_SetThrottle(40);
            Driver_SetSteering(-70);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1400 && distance > 150)
            {
                DState = S1;
                ticks_cnt = 0;
            }
            break;
        case S1:
            if (distance < 1000)
            {
                Driver_SetThrottle(60);
            }
            else if (distance < 3000)
            {
                Driver_SetThrottle(90);
            }
            else
            {
                Driver_SetThrottle(40);
            }
            Driver_SetSteering(AL_Regler());
            if (Driver_GetFrontDist() < 1400)
            {
                if (rpm_speed > 2000)
                {
                    Driver_SetThrottle(-50);
                }
                else
                {
                    Driver_SetThrottle(40);
                }
            }
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 4800)
            {
                DState = T1;
                ticks_cnt = 0;
            }
            break;
    }
}

int16_t AL_Regler(void)
{
    return (sen_diff * kp) + (sen_diff_delta * time_delta_inv * kd);
}

void AL_Recovery(void)
{
    Driver_SetThrottle(-40);
}
