#include "driver_general.h"
#include "driver_aktorik.h"
#include "driver_lcd.h"

#define DIR_CCW     0
#define DIR_CW      1
#define DIR_TEST    2

extern uint8_t Direction;

void Driver_Init(void)
{
    Driver_LCD_Init();

    Driver_LCD_WriteString("Motor Init...", 2, 28);
    Driver_LCD_WriteString("Direction: ", 4, 0);

    switch (Direction)
    {
        case DIR_CCW:
            Driver_LCD_WriteString("CCW", 4, 66);
            break;
        case DIR_CW:
            Driver_LCD_WriteString("CW", 4, 66);
            break;
        case DIR_TEST:
            Driver_LCD_WriteString("Test", 4, 66);
            break;
    }

    Driver_LCD_WriteString("[CrazyCar]", 6, 0);
    Driver_LCD_WriteString("Team: Gsengte Sau", 7, 0);

    Driver_SteeringInit();
    Driver_ThrottleInit();
}
