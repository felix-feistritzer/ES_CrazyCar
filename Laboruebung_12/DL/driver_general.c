#include "driver_general.h"
#include "driver_aktorik.h"
#include "driver_lcd.h"

void Driver_Init(void)
{
    Driver_LCD_Init();

    Driver_LCD_WriteString("Motor Init...", 3, 28);
    Driver_LCD_WriteString("[CrazyCar]", 6, 0);
    Driver_LCD_WriteString("Team: Gsengte Sau", 7, 0);

    Driver_SteeringInit();
    Driver_ThrottleInit();
}
