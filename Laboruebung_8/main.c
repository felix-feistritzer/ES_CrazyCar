#include <msp430.h>
#include <stdint.h>

#include "hal_general.h"
#include "hal_gpio.h"
#include "hal_usciB1.h"
#include "driver_general.h"
#include "driver_aktorik.h"
#include "driver_lcd.h"
#include "hal_adc12.h"

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

	uint8_t text[8] = {'H', 'e', 'l', 'l', 'o', ' ', ' ', ' '};
	Driver_LCD_WriteText(text, 5, 1, 49);

	uint8_t textAdc[6] = {'[', 'R', 'g', 'h', 't', ']'};
	Driver_LCD_WriteText(textAdc, 6, 3, 0);
	textAdc[1] = 'L';
	textAdc[2] = 'e';
	textAdc[3] = 'f';
	textAdc[4] = 't';
	Driver_LCD_WriteText(textAdc, 6, 4, 0);
	textAdc[1] = 'F';
    textAdc[2] = 'r';
    textAdc[3] = 'n';
    textAdc[4] = 't';
	Driver_LCD_WriteText(textAdc, 6, 5, 0);
	textAdc[1] = 'V';
    textAdc[2] = 'B';
    textAdc[3] = 'a';
    textAdc[4] = 't';
	Driver_LCD_WriteText(textAdc, 6, 6, 0);
    textAdc[1] = 'S';
    textAdc[2] = 'p';
    textAdc[3] = 'e';
    textAdc[4] = 'd';
    Driver_LCD_WriteText(textAdc, 6, 7, 0);


	while(1 == 1)
	{
	    if (adcCom.Status.B.ADCrdy == 1)
	    {
	        uint8_t i;
	        for (i = 0; i < 4; i++)
	        {
                IntToASCII(text, adcCom.ADCBuffer[i]);
                Driver_LCD_WriteText(text, 4, i + 3, 102);
                Driver_LCD_DrawBar(adcCom.ADCBuffer[i], 4095, 60, i + 3, 36);
	        }

	        adcCom.Status.B.ADCrdy = 0;

	        IntToASCII(text, rpm_speed);
	        Driver_LCD_WriteText(text, 4, 7, 102);
	        Driver_LCD_DrawBar(rpm_speed, 600, 60, 7, 36);
	    }

	    if (buttonCom.active == 1)
        {
            switch (buttonCom.button)
            {
                case 0:
                    Driver_SetThrottle(50);
                    break;
                case 1:
                    Driver_SetThrottle(0);
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
