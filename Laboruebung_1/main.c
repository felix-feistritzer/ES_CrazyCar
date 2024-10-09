#include <msp430.h> 
#include "hal_general.h"


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	HAL_Init();

	while(1 == 1)
	{

	}
}
