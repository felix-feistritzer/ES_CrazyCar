#include "driver_general.h"
#include "driver_aktorik.h"
#include "driver_lcd.h"

void Driver_Init(void)
{
    Driver_LCD_Init();

    Driver_LCD_WriteString("Motor Init...", 3, 28);

    Driver_SteeringInit();
    Driver_ThrottleInit();
}
