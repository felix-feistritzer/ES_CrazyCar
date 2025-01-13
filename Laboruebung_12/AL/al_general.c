#include "al_general.h"
#include "driver_lcd.h"
#include "al_algorithm.h"

State_t CCState;
extern DriveState_t DState;

void AL_Init(void)
{
    Driver_LCD_Clear();
    Driver_LCD_WriteString("Driving...", 1, 40);

    DState = INIT;

    TA1CCTL0 |= CCIE;   // Timer_A1: CCR0 Capture/Compare interrupt enable


    // TA1CCTL0 &= ~CCIE;  // Timer_A1: CCR0 Capture/Compare interrupt disable
}
