#include "al_general.h"
#include "driver_lcd.h"
#include "al_algorithm.h"
#include "hal_timerA2.h"

volatile State_t CCState;
extern DriveState_t DState;

void AL_Init(void)
{
    Driver_LCD_Clear();
    CCState = Data;
}

void AL_CCW(void)
{
    Driver_LCD_Clear();
    Driver_LCD_WriteString("Driving...", 3, 28);

    HAL_TimerA2_Start();

    DState = INIT;
}

void AL_Stop()
{
    HAL_TimerA2_Stop();

    Driver_LCD_Clear();
    // Driver_LCD_WriteString("Stop", 3, 40);
}
