#ifndef _HAL_USCIB1_H_
#define _HAL_USCIB1_H_

#include <msp430.h>
#include <stdint.h>
#include "hal_gpio.h"

#define PRESCALE_SPI_B1 0x19    // 2.5MHz / 100kHz = 25

typedef struct {
    struct{
        uint8_t TxSuc;          // Bit=1 wenn Daten übertragen wurden
    }Status;

    struct {
        uint8_t len;            // Länge der Daten in Bytes die übertragen werden
        uint8_t cnt;            // Index auf momentan übertragene Daten
        uint8_t Data[256];      // Tx Daten Array
    }TxData;

    struct {
        uint8_t len;            // Länge der empfangenen Daten
        uint8_t Data[256];      // Rx Daten Array
    }RxData;
}USCIB1_SPICOM;

void HAL_USCIB1_Init(void);
void HAL_USCIB1_Transmit(void);

#endif
