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
float throttle_integral;

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
            Driver_LCD_WriteString("[Thrt]", 6, 0);
            Driver_LCD_WriteString("[mm/s]", 7, 0);
            break;
        case START_T:
            if (distance < 1000)
            {
                AL_SetSpeed(1000);
            }
            else if (distance < 4000)
            {
                AL_SetSpeed(4000);
            }
            else
            {
                AL_SetSpeed(1000);
            }
            Driver_SetSteering(AL_Regler());

            Driver_LCD_IntToASCII(text, rpm_speed);
            Driver_LCD_WriteText(text, 4, 7, 102);
            Driver_LCD_DrawBar(rpm_speed, 5000, 60, 7, 36);

            if (Driver_GetFrontDist() < 200)
            {
                DState_Test = STOP_T;
                ticks_cnt = 0;
            }

        case STOP_T:
            Driver_SetThrottle(0);
            break;
    }
}

void AL_SetSpeed(int16_t target_speed)
{
    int16_t error = target_speed - rpm_speed;
    int16_t throttle;

    if (error < -500)
    {
        throttle = -50;
    }
    else
    {
        float error_integral = error * 0.0167;
        throttle_integral = throttle_integral + error_integral;

        throttle = error * 0.2 + throttle_integral * 0.05;

        if (throttle > 100)
        {
            throttle = 70;
            throttle_integral = throttle_integral - error_integral;
        }
        else if (throttle < 30)
        {
            throttle = 30;
            throttle_integral = throttle_integral - error_integral;
        }
    }

    Driver_SetThrottle(throttle);

    Driver_LCD_IntToASCII(text, throttle);
    Driver_LCD_WriteText(text, 4, 6, 102);
    Driver_LCD_DrawBar(throttle, 100, 60, 6, 36);

}

void AL_Break(int16_t target_speed)
{

}
