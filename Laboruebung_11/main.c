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

extern ButtonCom     buttonCom;
extern USCIB1_SPICOM spiCom;
extern ADC12Com      adcCom;
extern uint16_t      rpm_speed;

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

	while(1 == 1)
	{
	    if (adcCom.Status.B.ADCrdy == 1)
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

	    /*
        uint8_t i;

	    if (buttonCom.active == 1)
        {
            switch (buttonCom.button)
            {
                case 0:
                    for (i = 0; i < 4; i++)
                    {
                        IntToASCII(text, adcCom.ADCBuffer[i]);
                        Driver_LCD_WriteText(text, 4, i + 3, 102);
                        Driver_LCD_DrawBar(adcCom.ADCBuffer[i], 4095, 60, i + 3, 36);
                    }

                    adcCom.Status.B.ADCrdy = 0;

                    IntToASCII(text, rpm_speed);
                    Driver_LCD_WriteText(text, 4, 7, 102);
                    Driver_LCD_DrawBar(rpm_speed, 5000, 60, 7, 36);
                    break;
                default:
                    break;
            }

            buttonCom.active = 0;   // Clear Flag
        }
        */
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
