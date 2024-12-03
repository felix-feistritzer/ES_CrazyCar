#ifndef _HAL_ADC12_H_
#define _HAL_ADC12_H_

#include <stdint.h>

typedef struct
{
    union{
        uint8_t R;
        struct
        {
                uint8_t ADCrdy:1; // Bit=1 wenn Daten übertragen wurden
                uint8_t dummy:7;
        }B;
    }Status;
    uint16_t ADCBuffer[4]; // Speicherplatz der ADC Werte
}ADC12Com;

void HAL_ADC12_Init(void);

#endif
