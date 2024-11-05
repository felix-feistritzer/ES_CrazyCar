#include <msp430.h> 

#include "hal_general.h"
#include "hal_gpio.h"
#include "hal_usciB1.h"
#include "driver_general.h"
#include "driver_aktorik.h"

extern ButtonCom buttonCom;
extern USCIB1_SPICOM spiCom;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	HAL_Init();
	Driver_Init();

	spiCom.TxData.Data[0] = 0xCC;
	spiCom.TxData.Data[1] = 0x55;
	spiCom.TxData.Data[2] = 0x77;
	spiCom.TxData.Data[3] = 0x00;
	spiCom.TxData.len = 3;
	spiCom.TxData.cnt = 0;
	spiCom.RxData.len = 0;
	spiCom.Status.TxSuc = 1;

	while(1 == 1)
	{
	    if (buttonCom.active == 1)
	    {
	        switch (buttonCom.button)
	        {
	            case 0:             // START_BUTTON
	                LCD_BL_ON;
	                // Driver_SetThrottle(50);
	                HAL_USCIB1_Transmit();
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
