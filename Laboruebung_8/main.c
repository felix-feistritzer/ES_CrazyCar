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

void IntToASCII(uint8_t *text, uint16_t value);

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	HAL_Init();
	Driver_Init();

	uint8_t text[8] = {'H', 'e', 'l', 'l', 'o', ' ', ' ', ' '};
	Driver_LCD_WriteText(text, 5, 1, 49);

	uint8_t textAdc[6] = {'A', 'D', 'C', '[', '0', ']'};
	Driver_LCD_WriteText(textAdc, 6, 3, 0);
	textAdc[4] = '1';
	Driver_LCD_WriteText(textAdc, 6, 4, 0);
	textAdc[4] = '2';
	Driver_LCD_WriteText(textAdc, 6, 5, 0);
	textAdc[4] = '3';
	Driver_LCD_WriteText(textAdc, 6, 6, 0);


	while(1 == 1)
	{
	    if (adcCom.Status.B.ADCrdy == 1)
	    {
	        uint8_t i;
	        for (i = 0; i < 4; i++)
	        {
                IntToASCII(text, adcCom.ADCBuffer[i]);
                Driver_LCD_WriteText(text, 8, i + 3, 49);
	        }

	        adcCom.Status.B.ADCrdy = 0;
	    }
	}
}

void IntToASCII(uint8_t *text, uint16_t value)
{
    uint8_t i;
    for (i = 8; i > 0; --i)
    {
        text[i - 1] = (value % 10) + 48;
        value = value / 10;
    }
}
