#include "al_algorithm.h"
#include "driver_aktorik.h"
#include "driver_sensor.h"
#include "hal_adc12.h"
#include "hal_timerA0.h"

//###############################
//# Global Variables
//###############################

// Extern
extern ADC12Com adcCom;
extern uint16_t ticks_cnt;
extern uint16_t rpm_speed;

// Driving State
DriveState_t DState;

// Sensors
uint16_t distance;
int16_t sen_diff_old;
int16_t sen_diff;
int16_t sen_diff_delta;

// Integral for Throttle
int16_t throttle_integral;

// Recovery
uint8_t stuck_cnt;
uint8_t recovery;
uint16_t recovery_distance;
uint16_t stuck_ticks;

//###############################
//# Algorithm CCW
//###############################

void AL_Algorithm_CCW(void)
{
    // Calculate Distance
    distance = ticks_cnt * 5; // Distance in mm

    // Difference Quotient Distance
    sen_diff_old = sen_diff;
    sen_diff = Driver_GetRightDist() - Driver_GetLeftDist();
    sen_diff_delta = sen_diff - sen_diff_old;

    //#### Recovery Algorithm ####
    //#
    if (DState == INIT)
    {
        stuck_cnt = 0;
        recovery = 0;
        recovery_distance = 0;
    }

    if (Driver_GetFrontDist() < 100)
    {
        stuck_cnt++;
    }
    else
    {
        stuck_cnt = 0;
    }

    if (stuck_cnt > 30)
    {
        recovery = 1;
        stuck_ticks = ticks_cnt;
        stuck_cnt = 0;
    }

    if (recovery == 1)
    {
        recovery_distance = (ticks_cnt - stuck_ticks) * 5;
        if (recovery_distance < 300)
        {
            Driver_SetThrottle(-40);
            Driver_SetSteering(0);

            return;
        }
        else
        {
            recovery_distance = 0;
            recovery = 0;
            ticks_cnt = ticks_cnt - stuck_ticks;
        }
    }

    //#
    //#### Recovery Algorithm End ####

    //#### CCW Algorithm ####
    //#
    switch (DState)
    {
        case INIT:
            ticks_cnt = 0;
            throttle_integral = 0;
            DState = START;
            break;
        case START:
            Driver_SetSteering(AL_Regler());
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(3000);
            }
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 1000)
            {
                DState = T1;
                ticks_cnt = 0;
            }
            break;
        case T1:
            AL_SetSpeed(1300);
            Driver_SetSteering(-50);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1000 && distance > 150)
            {
                DState = S2;
                ticks_cnt = 0;
            }
            break;
        case S2:
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(2000);
            }
            Driver_SetSteering(AL_Regler());
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 1000)
            {
                DState = T2;
                ticks_cnt = 0;
            }
            break;
        case T2:
            AL_SetSpeed(1300);
            Driver_SetSteering(-70);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1000 && distance > 150)
            {
                DState = S3;
                ticks_cnt = 0;
            }
            break;
        case S3:
            if (distance > 1600)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(2000);
            }
            Driver_SetSteering(AL_Regler());
            if (Driver_GetLeftDist() > 750 && distance > 1600)
            {
                DState = T3;
                ticks_cnt = 0;
            }
            break;
        case T3:
            AL_SetSpeed(1000);
            Driver_SetSteering(-100);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1400 && distance > 500)
            {
                DState = S4;
                ticks_cnt = 0;
            }
            break;
        case S4:
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(2000);
            }
            Driver_SetSteering(AL_Regler());
            if (Driver_GetRightDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 800)
            {
                DState = T4;
                ticks_cnt = 0;
            }
            break;
        case T4:
            AL_SetSpeed(1100);
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
                AL_SetSpeed(3000);
            }
            else
            {
                AL_SetSpeed(1300);
            }
            Driver_SetSteering(AL_Regler());
            if (Driver_GetRightDist() > 750 && distance > 2000)
            {
                DState = T5;
                ticks_cnt = 0;
            }
            break;
        case T5:
            AL_SetSpeed(1400);
            Driver_SetSteering(100);
            if (Driver_GetRightDist() < 600 && distance > 150)
            {
                DState = S6;
                ticks_cnt = 0;
            }
            break;
        case S6:
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(2000);
            }
            Driver_SetSteering(AL_Regler_right(350));
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 750 && distance > 400)
            {
                DState = T6;
                ticks_cnt = 0;
            }
            break;
        case T6:
            AL_SetSpeed(1100);
            Driver_SetSteering(-70);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1400 && distance > 150)
            {
                DState = S7;
                ticks_cnt = 0;
            }
            break;
        case S7:
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(1500);
            }
            Driver_SetSteering(AL_Regler());
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 800 && distance > 500)
            {
                DState = T7;
                ticks_cnt = 0;
            }
            break;
        case T7:
            AL_SetSpeed(1100);
            Driver_SetSteering(-70);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1400 && distance > 150)
            {
                DState = S8;
                ticks_cnt = 0;
            }
            break;
        case S8:
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(1500);
            }
            Driver_SetSteering(AL_Regler());
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 800 && distance > 900)
            {
                DState = T8;
                ticks_cnt = 0;
            }
            break;
        case T8:
            AL_SetSpeed(1100);
            Driver_SetSteering(-50);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1400 && distance > 150)
            {
                DState = S1;
                ticks_cnt = 0;
            }
            break;
        case S1:
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(4000);
            }
            Driver_SetSteering(AL_Regler());
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 4800)
            {
                DState = T1;
                ticks_cnt = 0;
            }
            break;
    }
    //#
    //#### CCW Algorithm End ####
}

//###############################
//# Algorithm CW
//###############################

void AL_Algorithm_CW(void)
{
    // Calculate Distance
    distance = ticks_cnt * 5; // Distance in mm

    // Difference Quotient Distance
    sen_diff_old = sen_diff;
    sen_diff = Driver_GetRightDist() - Driver_GetLeftDist();
    sen_diff_delta = sen_diff - sen_diff_old;

    //#### Recovery Algorithm ####
    //#
    if (DState == INIT)
    {
        stuck_cnt = 0;
        recovery = 0;
        recovery_distance = 0;
    }

    if (Driver_GetFrontDist() < 100)
    {
        stuck_cnt++;
    }
    else
    {
        stuck_cnt = 0;
    }

    if (stuck_cnt > 30)
    {
        recovery = 1;
        stuck_ticks = ticks_cnt;
        stuck_cnt = 0;
    }

    if (recovery == 1)
    {
        recovery_distance = (ticks_cnt - stuck_ticks) * 5;
        if (recovery_distance < 300)
        {
            Driver_SetThrottle(-40);
            Driver_SetSteering(0);

            return;
        }
        else
        {
            recovery_distance = 0;
            recovery = 0;
            ticks_cnt = ticks_cnt - stuck_ticks;
        }
    }
    //#
    //#### Recovery Algorithm End ####

    //#### CW Algorithm ####
    //#
    switch (DState)
    {
        case INIT:
            ticks_cnt = 0;
            throttle_integral = 0;
            DState = START;
            break;
        case START:
            Driver_SetSteering(AL_Regler());

            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(4000);
            }
            if (Driver_GetRightDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 1000)
            {
                DState = T1;
                ticks_cnt = 0;
            }
            break;
        case T1:
            Driver_SetSteering(100);
            AL_SetSpeed(1300);
            if (Driver_GetRightDist() < 750 && Driver_GetFrontDist() > 1000 && distance > 150)
            {
                DState = S2;
                ticks_cnt = 0;
            }
            break;
        case S2:
            Driver_SetSteering(AL_Regler());
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(2000);
            }
            if (Driver_GetRightDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 1000)
            {
                DState = T2;
                ticks_cnt = 0;
            }
            break;
        case T2:
            Driver_SetSteering(80);
            AL_SetSpeed(1300);
            if (Driver_GetRightDist() < 750 && Driver_GetFrontDist() > 1000 && distance > 150)
            {
                DState = S3;
                ticks_cnt = 0;
            }
            break;
        case S3:
            Driver_SetSteering(AL_Regler());
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(2000);
            }
            if (Driver_GetRightDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 500)
            {
                DState = T3;
                ticks_cnt = 0;
            }
            break;
        case T3:
            Driver_SetSteering(80);
            AL_SetSpeed(1300);
            if (Driver_GetFrontDist() > 1000 && distance > 150)
            {
                DState = S4;
                ticks_cnt = 0;
            }
            break;
        case S4:
            Driver_SetSteering(AL_Regler_left(350));
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(2000);
            }
            else
            {
                AL_SetSpeed(1000);
            }
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 100)
            {
                DState = T4;
                ticks_cnt = 0;
            }
            break;
        case T4:
            Driver_SetSteering(-60);
            AL_SetSpeed(1200);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1000 && distance > 150)
            {
                DState = S5;
                ticks_cnt = 0;
            }
            break;
        case S5:
            Driver_SetSteering(AL_Regler());
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(2000);
            }
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 2000)
            {
                DState = T5;
                ticks_cnt = 0;
            }
            break;
        case T5:
            Driver_SetSteering(-100);
            AL_SetSpeed(1100);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1400 && distance > 500)
            {
                DState = S6;
                ticks_cnt = 0;
            }
            break;
        case S6:
            Driver_SetSteering(AL_Regler());
            if (distance > 900)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(2000);
            }
            if (Driver_GetRightDist() > 750 && distance > 800)
            {
                DState = T6;
                ticks_cnt = 0;
            }
            break;
        case T6:
            Driver_SetSteering(100);
            AL_SetSpeed(1200);
            if (Driver_GetRightDist() < 750 && Driver_GetFrontDist() > 1400 && distance > 500)
            {
                DState = S7;
                ticks_cnt = 0;
            }
            break;
        case S7:
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(2000);
            }
            Driver_SetSteering(AL_Regler());
            if (Driver_GetRightDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 1600)
            {
                DState = T7;
                ticks_cnt = 0;
            }
            break;
        case T7:
            Driver_SetSteering(100);
            AL_SetSpeed(1300);
            if (Driver_GetRightDist() < 750 && Driver_GetFrontDist() > 1000 && distance > 150)
            {
                DState = S8;
                ticks_cnt = 0;
            }
            break;
        case S8:
            Driver_SetSteering(AL_Regler());
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(2000);
            }
            if (Driver_GetRightDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 1000)
            {
                DState = T8;
                ticks_cnt = 0;
            }
            break;
        case T8:
            Driver_SetSteering(100);
            AL_SetSpeed(1300);
            if (Driver_GetLeftDist() < 750 && Driver_GetFrontDist() > 1000 && distance > 150)
            {
                DState = S1;
                ticks_cnt = 0;
            }
            break;
        case S1:
            Driver_SetSteering(AL_Regler());
            if (Driver_GetFrontDist() < 1400)
            {
                AL_SetSpeed(1000);
            }
            else
            {
                AL_SetSpeed(4000);
            }
            if (Driver_GetRightDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 4800)
            {
                DState = T1;
                ticks_cnt = 0;
            }
            break;
    }
    //#
    //#### CW Algorithm End ####
}

//###############################
//# Regler Functions
//###############################

//#### Steering PD-Regler ####
int16_t AL_Regler(void)
{
    const int16_t kp = 3277; // 0.1 * 32767
    const int16_t kd = 328;  // 0.01 * 32767
    const uint8_t dt_inv = 60;

    int32_t result;
    int32_t result_p;
    int32_t result_d;

    result_p = (int32_t)sen_diff * kp;

    result_d = (int32_t)sen_diff_delta * dt_inv;
    result_d = (int32_t)result_d * kd;

    result = result_p + result_d;
    result = result >> 15;

    return (int16_t)result;
}

//#### Steering P-Regler (only Left Wall) ####
int16_t AL_Regler_left(uint16_t right_dist)
{
    const int16_t kp = 6553; // 0.1 * 2 * 32767

    int32_t result_p;
    int16_t sen_diff;

    sen_diff = right_dist - Driver_GetLeftDist();

    result_p = (int32_t)sen_diff * kp;
    result_p = result_p >> 15;

    return (int16_t)result_p;
}

//#### Steering P-Regler (only Right Wall) ####
int16_t AL_Regler_right(uint16_t left_dist)
{
    const int16_t kp = 6553; // 0.1 * 2 * 32767

    int32_t result_p;
    int16_t sen_diff;

    sen_diff = Driver_GetRightDist() - left_dist;

    result_p = (int32_t)sen_diff * kp;
    result_p = result_p >> 15;

    return result_p;
}

//#### Throttle PI-Regler ####
void AL_SetSpeed(int16_t target_speed)
{
    const int16_t dt = 546;           // (1 / 60) * 32767
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
