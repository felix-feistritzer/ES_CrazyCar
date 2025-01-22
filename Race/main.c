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
#include "al_test.h"

#define DIR_CCW     0
#define DIR_CW      1
#define DIR_TEST    2

//#### Set Direction ####
const uint8_t Direction = DIR_TEST;

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
                    switch (Direction)
                    {
                        case DIR_CCW:
                            AL_CCW();
                            break;
                        case DIR_CW:
                            AL_CW();
                            break;
                        case DIR_TEST:
                            AL_Test();
                            break;
                    }
                    break;
                case 1:                 // Stop CrazyCar
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
	                AL_Algorithm_CCW();
	                A2_Flag = 0;
	            }
	            break;
	        case CW:
	            if (A2_Flag == 1)
                {
                    AL_Algorithm_CW();
                    A2_Flag = 0;
                }
                break;
	        case Stop:
	            AL_Data_Init();
	            CCState = Data;
	            break;
	        case Test:
	            if (A2_Flag == 1)
                {
                    AL_Algorithm_Test();
                    A2_Flag = 0;
                }
	            break;
	    }
	}
}
