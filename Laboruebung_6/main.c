#include <msp430.h> 

#include "hal_general.h"
#include "hal_gpio.h"
#include "hal_usciB1.h"
#include "driver_general.h"
#include "driver_aktorik.h"
#include "driver_lcd.h"

extern ButtonCom buttonCom;
extern USCIB1_SPICOM spiCom;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	HAL_Init();
	Driver_Init();

	uint8_t text1[5] = {'H', 'e', 'l', 'l', 'o'};
	Driver_LCD_WriteText(text1, 5, 1, 49);


	while(1 == 1)
	{
	    if (buttonCom.active == 1)
	    {
	        switch (buttonCom.button)
	        {
	            case 0:             // START_BUTTON
	                LCD_BL_ON;
	                //Driver_SetThrottle(50);
	                break;

	            case 1:             // STOP_BUTTON
	                LCD_BL_OFF;
	                // Driver_SetThrottle(0);
	                break;
	        }

	        buttonCom.active = 0;   // Clear Flag
	    }
	}
}
