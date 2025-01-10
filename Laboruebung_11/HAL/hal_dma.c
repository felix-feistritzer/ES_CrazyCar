#include <msp430.h>
#include "hal_dma.h"
#include "hal_adc12.h"

extern ADC12Com adcCom;

void HAL_DMA_Init(void)
{
    DMA0CTL |= DMADT_5;                 // Repeated block transfer
    DMA0CTL |= DMADSTINCR_3;            // Increment destination address
    DMA0CTL |= DMASRCINCR_3;            // Increment source address
    DMA0CTL |= DMAIE;                   // Enable Interrupt
    DMA0CTL &= ~DMAIFG;                 // Delete Interrupt-flag if it is pending
    DMACTL0 |= DMA0TSEL_24;             // Use Interrupt-Flag of ADC12
    DMA0SA = &ADC12MEM0;                // Source address = ADC12 Memory Register
    DMA0DA = &adcCom.ADCBuffer;         // Destination address = Buffer of ADC
    DMA0SZ = 4;                         // 4 words to transfer

    DMA0CTL |= DMAEN;                   // Enable DMA
}

#pragma vector = DMA_VECTOR
__interrupt void DMA_ISR(void)
{
    adcCom.Status.B.ADCrdy = 1;
    ADC12CTL0 |= ADC12ENC ;             // enable conversation
    DMA0CTL &= ~DMAIFG ;                // reset IR Bit
}
