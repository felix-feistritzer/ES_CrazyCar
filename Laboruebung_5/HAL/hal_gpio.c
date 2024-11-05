#include "hal_gpio.h"

extern ButtonCom buttonCom;

void HAL_GPIO_Init(void)
{
    // Port 1
    P1DIR &= 0x00;      // Input
    P1REN |= 0xFF;      // Resistor Enable
    P1OUT &= 0x00;      // Pulldown Resistor
    P1SEL &= 0x00;      // I/0 Function

    // Port 2
    P2DIR &= 0x00;
    P2REN |= 0xFF;
    P2OUT &= 0x00;
    P2SEL &= 0x00;

    // Port 3
    P3DIR &= 0x00;
    P3REN |= 0xFF;
    P3OUT &= 0x00;
    P3SEL &= 0x00;

    // Port 4
    P4DIR &= 0x00;
    P4REN |= 0xFF;
    P4OUT &= 0x00;
    P4SEL &= 0x00;

    // Port 5
    P5DIR &= 0x00;
    P5REN |= 0xFF;
    P5OUT &= 0x00;
    P5SEL &= 0x00;

    // Port 6
    P6DIR &= 0x00;
    P6REN |= 0xFF;
    P6OUT &= 0x00;
    P6SEL &= 0x00;

    // Port 7
    P7DIR &= 0x00;
    P7REN |= 0xFF;
    P7OUT &= 0x00;
    P7SEL &= 0x00;

    // Port 8
    P8DIR &= 0x00;
    P8REN |= 0xFF;
    P8OUT &= 0x00;
    P8SEL &= 0x00;

    // Port 9
    P9DIR &= 0x00;
    P9REN |= 0xFF;
    P9OUT &= 0x00;
    P9SEL &= 0x00;

//***********************************
    // Port 1
    // RPM_SENSOR
    P1DIR &= ~RPM_SENSOR;   // Input
    P1OUT |= RPM_SENSOR;    // Pullup Resistor
    P1SEL |= RPM_SENSOR;    // TimerA0.2 select

    // START_BUTTON
    P1DIR &= ~START_BUTTON; // Input
    P1OUT |= START_BUTTON;  // Pullup Resistor
    P1IES &= ~START_BUTTON; // Rising Edge
    P1IE  |= START_BUTTON;  // Interrupt Enabled

    // STOP_BUTTON
    P1DIR &= ~STOP_BUTTON;  // Input
    P1OUT |= STOP_BUTTON;   // Pullup Resistor
    P1IES &= ~STOP_BUTTON;  // Rising Edge
    P1IE  |= STOP_BUTTON;   // Interrupt Enabled

    // Port 3
    // THROTTLE
    P3DIR |= THROTTLE;      // Output
    P3SEL |= THROTTLE;      // TimerA1.1 select

    // STEERING
    P3DIR |= STEERING;      // Output
    P3SEL |= STEERING;      // TimerA1.2 select

    // SMCLK
    P3DIR |= SMCLK;         // Output
    P3SEL |= SMCLK;         // SMCLK function selected

    // Port 7
    // XT2IN and XT2OUT
    P7SEL |= XT2IN;         // XT2 function selected
    P7SEL |= XT2OUT;        // XT2 function selected
    UCSCTL6 &= ~XT2BYPASS;  // Source from external crystal

    // Port 8
    P8DIR |= LCD_BL;        // Output
    P8DIR |= LCD_SPI_CS;    // Output
    P8SEL |= LCD_SPI_CLK;   // LCD_SPI_CLK function selected
    P8SEL |= LCD_SPI_MOSI;  // LCD_SPI_MOSI function selected
    P8SEL |= LCD_SPI_MISO;  // LCD_SPI_MISO function selected

//***********************************

    __enable_interrupt();
    P1IFG &= 0x00;          // Clear Interrupt Flags (see Family Guide Note 12.2.7)
}

// Interrupts

#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR(void)
{
    buttonCom.active = 1;
    switch (P1IFG)
    {
        case START_BUTTON:
            buttonCom.button = 0;
            break;
        case STOP_BUTTON:
            buttonCom.button = 1;
            break;
        default:
            buttonCom.button = 2;
    }

    P1IFG &= 0x00;  // Clear Interrupt Flags
}
