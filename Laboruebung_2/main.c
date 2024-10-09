#include <msp430.h> 
#include "hal_general.h"
#include "hal_gpio.h"
#include <stdint.h>

// Globale variables for calculation comparison
/*
uint16_t int_a = 27416;
uint16_t int_b = 13881;
uint32_t int_result;

float float_a = 27.416;
float float_b = 13.881;
double double_result;
*/

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
	                LCD_BL_ON;      //LCD EIN
	                break;
	            case 1:             // STOP_BUTTON
	                LCD_BL_OFF;     //LCD OFF
	                break;
	        }

	        buttonCom.active = 0;   // Clear Flag
	    }

	    /*
	    // Integer Multiplication
	    int_result = int_a * int_b;
	    LCD_BL_ON;

	    // Floating Point Multiplication
	    double_result = float_a * float_b;
	    LCD_BL_OFF;
	    */
	}
}
