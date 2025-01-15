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

extern const uint8_t time_delta_inv;

uint8_t text[8];
int8_t throttle = 0;

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
            Driver_LCD_WriteString("[mm/s]", 7, 0);
            break;
        case START_T:
            AL_SetSpeed(1000);
            Driver_SetSteering(AL_Regler());

            Driver_LCD_IntToASCII(text, rpm_speed);
            Driver_LCD_WriteText(text, 4, 7, 102);
            Driver_LCD_DrawBar(rpm_speed, 5000, 60, 7, 36);

            if (Driver_GetFrontDist() < 500)
            {
                DState_Test = STOP_T;
                ticks_cnt = 0;
            }
            /*
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 1000)
            {
                DState_Test = T1_T;
                ticks_cnt = 0;
            }
            */
            break;
        case T1_T:
            Driver_SetThrottle(40);
            Driver_SetSteering(-100);
            if (Driver_GetFrontDist() > 1000 && distance > 150)
            {
                DState_Test = S2_T;
                ticks_cnt = 0;
            }
            break;
        case S2_T:
            Driver_SetThrottle(50);
            Driver_SetSteering(AL_Regler());
            if (Driver_GetLeftDist() > 750 && Driver_GetFrontDist() < 1000 && distance > 1000)
            {
                DState_Test = T2_T;
                ticks_cnt = 0;
            }
            break;
        case T2_T:
            Driver_SetThrottle(40);
            Driver_SetSteering(-100);
            if (Driver_GetFrontDist() > 1000 && distance > 150)
            {
                DState_Test = S3_T;
                ticks_cnt = 0;
            }
            break;
        case S3_T:
            Driver_SetThrottle(50);
            Driver_SetSteering(AL_Regler());
            if (distance > 1600)
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

void AL_SetSpeed(int16_t target_speed)
{
    int16_t speed_diff = target_speed - rpm_speed;

}

void AL_Break(int16_t target_speed)
{

}
