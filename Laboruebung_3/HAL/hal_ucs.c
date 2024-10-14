#include "hal_ucs.h"

void HAL_UCS_init(void)
{
    UCSCTL6 &= ~XT2OFF;     // XT2 is on
    UCSCTL3 |= SELREF_2;    // FFL reference set to REFOCLK
    UCSCTL4 |= SELA_2;      // ACLK source set to REFOCLK

    while (SFRIFG1 & OFIFG) // wait until all error flags are cleared and not set again
    {
        UCSCTL7 &= ~(XT2OFFG + DCOFFG + XT1HFOFFG + XT1LFOFFG);
        SFRIFG1 &= ~OFIFG;
    }

    UCSCTL6 &= ~XT2DRIVE_1; // XT2DRIVE set to current consumption 16 MHz to 24 MHz
    UCSCTL4 |= SELS_5;      // SMCLK source set to XT2CLK
    UCSCTL4 |= SELM_5;      // MCLK source set to XT2CLK
    UCSCTL5 |= DIVS_3;      // SMCLK source divider 1/8 => 2.5 MHz

}
