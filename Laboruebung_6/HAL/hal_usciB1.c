#include "hal_usciB1.h"

extern USCIB1_SPICOM spiCom;

void HAL_USCIB1_Init(void)
{
    UCB1CTL1 |= UCSWRST;        // Software reset enable

    UCB1CTL0 |= UCMODE_0;       // USCI Mode: 3-pin SPI
    UCB1CTL1 |= UCSSEL__SMCLK;  // USCI clock: Sub-Master Clock
    UCB1CTL0 |= UCMST;          // Master mode selected
    UCB1BR0 = PRESCALE_SPI_B1;  // Prescaler low byte: 25 * 100kHz = 2.5 MHz
    UCB1CTL0 &= ~UC7BIT;        // Character length: 8-bit
    UCB1CTL0 |= UCMSB;          // MSB first selected
    UCB1CTL0 &= ~UCCKPH;        // Clock Phase: 0
    UCB1CTL0 |= UCCKPL;         // Clock Polarity: 1

    UCB1CTL1 &= ~UCSWRST;       // Software reset disable

    UCB1IE |= UCRXIE;           // RX-Interrupt enable
}

void HAL_USCIB1_Transmit(void)
{
    if (spiCom.Status.TxSuc == 1)
    {
        spiCom.Status.TxSuc = 0;
        LCD_SPI_CS_LOW;
        UCB1TXBUF = spiCom.TxData.Data[0];
    }
}

#pragma vector = USCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void)
{
    if ((UCB1IE & UCRXIE) && (spiCom.Status.TxSuc == 0))
    {
        LCD_SPI_CS_HIGH;
        spiCom.RxData.Data[spiCom.RxData.len] = UCB1RXBUF;
        spiCom.RxData.len++;

        if (spiCom.TxData.cnt < spiCom.TxData.len)
        {
            LCD_SPI_CS_LOW;
            UCB1TXBUF = spiCom.TxData.Data[spiCom.TxData.cnt + 1];
            spiCom.TxData.cnt++;
        }
        else
        {
            spiCom.Status.TxSuc = 1;
            spiCom.TxData.cnt = 0;
        }
    }
}
