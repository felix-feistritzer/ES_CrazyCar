#include "al_general.h"
#include "driver_lcd.h"
#include "al_algorithm.h"
#include "hal_timerA2.h"
#include "driver_aktorik.h"
#include "al_test.h"

volatile State_t CCState;
extern DriveState_t DState;
extern DriveState_Test_t DState_Test;

void AL_Init(void)
{
    Driver_LCD_Clear();
    CCState = Data;
}

void AL_CCW(void)
{
    Driver_LCD_Clear();
    Driver_LCD_WriteString("Driving...", 3, 28);

    CCState = CCW;
    DState = INIT;

    HAL_TimerA2_Start();
}

void AL_Stop()
{
    Driver_SetThrottle(0);
    Driver_SetSteering(0);

    HAL_TimerA2_Stop();

    CCState = Stop;

    Driver_LCD_Clear();
    // Driver_LCD_WriteString("Stop", 3, 40);
}

void AL_Test(void)
{
    Driver_LCD_Clear();
    Driver_LCD_WriteString("Driving (Test)...", 3, 14);

    CCState = Test;
    DState_Test = INIT_T;

    HAL_TimerA2_Start();
}
