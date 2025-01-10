#include <msp430.h>
#include <stdint.h>

#include "hal_general.h"
#include "hal_gpio.h"
#include "hal_usciB1.h"
#include "driver_general.h"
#include "driver_aktorik.h"
#include "driver_lcd.h"
#include "hal_adc12.h"
#include "driver_sensor.h"
#include "al_general.h"

extern ButtonCom     buttonCom;
extern USCIB1_SPICOM spiCom;
extern ADC12Com      adcCom;
extern uint16_t      rpm_speed;
extern State_t       CCState;

void IntToASCII(uint8_t *text, uint16_t value);

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	HAL_Init();
	Driver_Init();

	Driver_LCD_Clear();

	Driver_LCD_WriteString("Data ADC", 1, 40);
	Driver_LCD_WriteString("[Rght]", 3, 0);
	Driver_LCD_WriteString("[Left]", 4, 0);
	Driver_LCD_WriteString("[Frnt]", 5, 0);
	//Driver_LCD_WriteString("[VBat]", 6, 0);
	Driver_LCD_WriteString("[mm/s]", 7, 0);

	uint8_t text[8];
	CCState = Data;

	while(1 == 1)
	{
	    if (adcCom.Status.B.ADCrdy == 1 && CCState == Data)
	    {
	        uint16_t rightDist = Driver_GetRightDist(adcCom.ADCBuffer[0]);
	        uint16_t leftDist  = Driver_GetLeftDist(adcCom.ADCBuffer[1]);
	        uint16_t frontDist = Driver_GetFrontDist(adcCom.ADCBuffer[2]);

	        IntToASCII(text, rightDist);
	        Driver_LCD_WriteText(text, 4, 3, 102);
	        Driver_LCD_DrawBar(rightDist, 800, 60, 3, 36);

	        IntToASCII(text, leftDist);
            Driver_LCD_WriteText(text, 4, 4, 102);
            Driver_LCD_DrawBar(leftDist, 800, 60, 4, 36);

            IntToASCII(text, frontDist);
            Driver_LCD_WriteText(text, 4, 5, 102);
            Driver_LCD_DrawBar(frontDist, 1500, 60, 5, 36);

	        adcCom.Status.B.ADCrdy = 0;

	        IntToASCII(text, rpm_speed);
	        Driver_LCD_WriteText(text, 4, 7, 102);
	        Driver_LCD_DrawBar(rpm_speed, 5000, 60, 7, 36);
	    }

	    if (buttonCom.active == 1)
        {
            switch (buttonCom.button)
            {
                case 0: // Start CrazyCar
                    CCState = Drive;
                    AL_Init();
                    break;
                case 1: // Stop CrazyCar
                    Driver_SetThrottle(0);
                    CCState = Stop;
                    Driver_LCD_Clear();
                    Driver_LCD_WriteString("Stop", 1, 40);
                    break;
            }

            buttonCom.active = 0;   // Clear Flag
        }
	}
}

void IntToASCII(uint8_t *text, uint16_t value)
{
    uint8_t i;
    for (i = 4; i > 0; --i)
    {
        text[i - 1] = (value % 10) + 48;
        value = value / 10;
    }
}
