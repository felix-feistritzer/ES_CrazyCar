#include "al_data.h"
#include "driver_lcd.h"
#include "driver_sensor.h"
#include "hal_adc12.h"
#include "hal_timerA0.h"

#define DIR_CCW     0
#define DIR_CW      1
#define DIR_TEST    2

extern uint8_t Direction;

extern ADC12Com adcCom;
extern uint16_t rpm_speed;

void AL_Data_Init(void)
{
    Driver_LCD_Clear();

    Driver_LCD_WriteString("Dir: ", 0, 0);

    switch (Direction)
    {
        case DIR_CCW:
            Driver_LCD_WriteString("CCW", 0, 30);
            break;
        case DIR_CW:
            Driver_LCD_WriteString("CW", 0, 30);
            break;
        case DIR_TEST:
            Driver_LCD_WriteString("Test", 0, 30);
            break;
    }

    Driver_LCD_WriteString("Data ADC", 1, 40);
    Driver_LCD_WriteString("[Rght]", 3, 0);
    Driver_LCD_WriteString("[Left]", 4, 0);
    Driver_LCD_WriteString("[Frnt]", 5, 0);
    Driver_LCD_WriteString("[Diff]", 6, 0);
    Driver_LCD_WriteString("[mm/s]", 7, 0);
}

void AL_Data(void)
{
    uint16_t rightDist = Driver_GetRightDist();
    uint16_t leftDist  = Driver_GetLeftDist();
    uint16_t frontDist = Driver_GetFrontDist();
    int16_t sen_diff = Driver_GetRightDist() - Driver_GetLeftDist();

    uint8_t text[8];

    Driver_LCD_IntToASCII(text, rightDist);
    Driver_LCD_WriteText(text, 4, 3, 102);
    Driver_LCD_DrawBar(rightDist, 800, 60, 3, 36);

    Driver_LCD_IntToASCII(text, leftDist);
    Driver_LCD_WriteText(text, 4, 4, 102);
    Driver_LCD_DrawBar(leftDist, 800, 60, 4, 36);

    Driver_LCD_IntToASCII(text, frontDist);
    Driver_LCD_WriteText(text, 4, 5, 102);
    Driver_LCD_DrawBar(frontDist, 1500, 60, 5, 36);

    Driver_LCD_IntToASCII(text, sen_diff < 0 ? -sen_diff : sen_diff);
    Driver_LCD_WriteText(text, 4, 6, 102);
    Driver_LCD_DrawBar(sen_diff < 0 ? -sen_diff : sen_diff, 800, 60, 6, 36);

    adcCom.Status.B.ADCrdy = 0;

    Driver_LCD_IntToASCII(text, rpm_speed);
    Driver_LCD_WriteText(text, 4, 7, 102);
    Driver_LCD_DrawBar(rpm_speed, 5000, 60, 7, 36);
}
