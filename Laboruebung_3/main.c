#include <msp430.h> 
#include "hal_general.h"
#include "hal_gpio.h"
#include <stdint.h>

extern ButtonCom buttonCom;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	HAL_Init();

	while(1 == 1)
	{
	    if (buttonCom.active == 1)
	    {
	        switch (buttonCom.button)
	        {
	            case 0:             // START_BUTTON
	                LCD_BL_ON;
	                break;
	            case 1:             // STOP_BUTTON
	                LCD_BL_OFF;
	                break;
	        }

	        buttonCom.active = 0;   // Clear Flag
	    }
	}
}
