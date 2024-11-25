#include "hal_adc12.h"
#include <msp430.h>

extern ADC12Com adcCom;

void HAL_ADC12_Init(void)
{
    // ADC12CTL0
    ADC12CTL0 &= ~ADC12ENC; // Disable Conversion

    // REFCTL0
    REFCTL0 |= REFVSEL_3;   // Reference Voltage Level Select 2.5V
    REFCTL0 |= REFON;       // Reference On
    REFCTL0 |= REFOUT;      // Reference output Buffer On

    // ADC12CTL0
    ADC12CTL0 |= ADC12SHT0_12;  // 1024 ADC12CLK cycles
    ADC12CTL0 |= ADC12SHT1_12;  // 1024 ADC12CLK cycles
    ADC12CTL0 |= ADC12MSC;      // Multiple SampleConversion
    ADC12CTL0 |= ADC12REFON;    // Reference on
    ADC12CTL0 |= ADC12REF2_5V;  // Ref 2.5V

    // ADC12MCTLx
    ADC12MCTL0 |= ADC12SREF_1;  // VRef+ and AVSS (GND)
    ADC12MCTL1 |= ADC12SREF_1;  // VRef+ and AVSS (GND)
    ADC12MCTL2 |= ADC12SREF_1;  // VRef+ and AVSS (GND)
    ADC12MCTL3 |= ADC12SREF_1;  // VRef+ and AVSS (GND)

    ADC12MCTL0 |= ADC12INCH_0;  // ADC12 Input Channel 0
    ADC12MCTL1 |= ADC12INCH_1;  // ADC12 Input Channel 1
    ADC12MCTL2 |= ADC12INCH_2;  // ADC12 Input Channel 2
    ADC12MCTL3 |= ADC12INCH_3;  // ADC12 Input Channel 3

    ADC12MCTL3 |= ADC12EOS;     // End of Sequence

    // ADC12CTL1
    ADC12CTL1 |= ADC12SHS_3;    // Sample/Hold Source: B0.1
    ADC12CTL1 |= ADC12SHP;      // SAMPCON signal is sourced from the sampling timer
    ADC12CTL1 |= ADC12DIV_3;    // Clock Divider /4
    ADC12CTL1 |= ADC12SSEL_3;   // Clock Source Select: SMCLK
    ADC12CTL1 |= ADC12CONSEQ_1; // Conversion Sequence Select: Sequence-of-channels

    ADC12IE |= ADC12IE3;        // Memory 3 Interrupt Enable
    ADC12CTL0 |= ADC12ON;       // ADC On
    ADC12CTL0 |= ADC12ENC;      // Enable Conversion
}

// Interrupt
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    adcCom.ADCBuffer[0] = ADC12MEM0;
    adcCom.ADCBuffer[1] = ADC12MEM1;
    adcCom.ADCBuffer[2] = ADC12MEM2;
    adcCom.ADCBuffer[3] = ADC12MEM3;

    adcCom.Status.B.ADCrdy = 1;
    ADC12IFG = 0x00;        // Clear Interrupt Flag
    ADC12CTL0 |= ADC12ENC;  // Enable Conversion
}


