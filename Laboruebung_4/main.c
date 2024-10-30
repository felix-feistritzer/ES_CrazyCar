#include <msp430.h> 

#include "hal_general.h"
#include "hal_gpio.h"
#include "driver_general.h"
#include "driver_aktorik.h"

extern ButtonCom buttonCom;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	HAL_Init();
	Driver_Init();

	while(1 == 1)
	{
	    if (buttonCom.active == 1)
	    {
	        switch (buttonCom.button)
	        {
	            case 0:             // START_BUTTON
	                LCD_BL_ON;
	                Driver_SetThrottle(50);
	                break;
	            case 1:             // STOP_BUTTON
	                LCD_BL_OFF;
	                Driver_SetThrottle(0);
	                break;
	        }

	        buttonCom.active = 0;   // Clear Flag
	    }
	}
}
