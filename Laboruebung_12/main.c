#include <msp430.h>
#include <stdint.h>

#include "hal_general.h"
#include "hal_gpio.h"
#include "hal_usciB1.h"
#include "hal_adc12.h"
#include "hal_timerA2.h"
#include "driver_general.h"
#include "driver_aktorik.h"
#include "driver_lcd.h"
#include "driver_sensor.h"
#include "al_general.h"
#include "al_data.h"
#include "al_algorithm.h"

extern ButtonCom     buttonCom;
extern ADC12Com      adcCom;
extern State_t       CCState;
extern uint8_t       A2_Flag;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	HAL_Init();
	Driver_Init();
	AL_Init();

	AL_Data_Init();

	while(1 == 1)
	{
	    if (buttonCom.active == 1)
            {
                switch (buttonCom.button)
                {
                    case 0:                 // Start CrazyCar
                        CCState = CCW;
                        AL_CCW();
                        break;
                    case 1:                 // Stop CrazyCar
                        Driver_SetThrottle(0);
                        CCState = Stop;
                        AL_Stop();
                        break;
                }

                buttonCom.active = 0;       // Clear Flag
            }

	    switch (CCState)
	    {
	        case Data:
	            if (adcCom.Status.B.ADCrdy == 1)
	            {
	                AL_Data();
	            }
	            break;
	        case CCW:
	            if (A2_Flag == 1)
	            {
	                AL_Algorithm();
	                A2_Flag = 0;
	            }
	            break;
	        case Stop:
	            AL_Data_Init();
	            CCState = Data;
	            break;
	    }
	}
}
