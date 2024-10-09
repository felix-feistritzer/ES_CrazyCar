#include "hal_gpio.h"

void HAL_GPIO_Init(void)
{
    // Port J
    PJDIR &= ~BIT0;             // IN
    PJDIR &= ~BIT1;             // IN
    PJDIR &= ~BIT2;             // IN
    PJDIR &= ~BIT3;             // IN

    PJREN |= BIT0;
    PJREN |= BIT1;
    PJREN |= BIT2;
    PJREN |= BIT3;

    PJOUT &= ~BIT0;
    PJOUT &= ~BIT1;
    PJOUT &= ~BIT2;
    PJOUT &= ~BIT3;

    // Port 1
    P1DIR &= ~BIT0;             // IN
    P1DIR &= ~BIT1;             // IN
    P1DIR &= ~BIT2;             // IN
    P1DIR &= ~RPM_SENSOR;       // IN
    P1DIR &= ~RPM_SENSOR_DIR;   // IN
    P1DIR |= I2C_INT_MOTION;    // OUT
    P1DIR &= ~START_BUTTON;     // IN
    P1DIR &= ~STOP_BUTTON;      // IN

    P1REN |= BIT0;
    P1REN |= BIT1;
    P1REN |= BIT2;

    P1OUT &= ~BIT0;
    P1OUT &= ~BIT1;
    P1OUT &= ~BIT2;

    // Port 2
    P2DIR &= ~DEBUG_TXD;        // IN
    P2DIR |= DEBUG_RXD;         // OUT
    P2DIR &= ~AUX_PIN_1;        // IN
    P2DIR &= ~AUX_PIN_2;        // IN
    P2DIR &= ~AUX_PIN_3;        // IN
    P2DIR &= ~AUX_PIN_4;        // IN
    P2DIR &= ~I2C_SDA_MOTION;   // IN
    P2DIR |= I2C_SCL_MOTION;    // OUT

    // Port 3
    P3DIR &= ~BIT0;             // IN
    P3DIR &= ~BIT1;             // IN
    P3DIR |= THROTTLE;          // OUT
    P3DIR |= STEERING;          // OUT
    P3DIR &= ~SMCLK;            // IN
    P3DIR &= ~BIT5;             // IN
    P3DIR &= ~BIT6;             // IN
    P3DIR |= DISTANCE_FRONT_EN; // OUT

    P3REN |= BIT0;
    P3REN |= BIT1;
    P3REN |= BIT5;
    P3REN |= BIT6;

    P3OUT &= ~BIT0;
    P3OUT &= ~BIT1;
    P3OUT &= ~BIT5;
    P3OUT &= ~BIT6;

    // Port 4
    P4DIR &= ~BIT0;             // IN
    P4DIR &= ~BIT1;             // IN
    P4DIR &= ~BIT2;             // IN
    P4DIR &= ~LINE_FOLLOW_2;    // IN
    P4DIR &= ~LINE_FOLLOW_1;    // IN
    P4DIR &= ~LINE_FOLLOW_3;    // IN
    P4DIR &= ~LINE_FOLLOW_4;    // IN
    P4DIR &= ~LINE_FOLLOW_5;    // IN

    P4REN |= BIT0;
    P4REN |= BIT1;
    P4REN |= BIT2;

    P4OUT &= ~BIT0;
    P4OUT &= ~BIT1;
    P4OUT &= ~BIT2;

    // Port 5
    P5DIR &= ~BIT0;             // IN
    P5DIR &= ~BIT1;             // IN
    P5DIR &= ~BIT2;             // IN
    P5DIR &= ~BIT3;             // IN
    P5DIR &= ~BIT4;             // IN
    P5DIR &= ~BIT5;             // IN
    P5DIR &= ~BIT6;             // IN
    P5DIR &= ~BIT7;             // IN

    P5REN |= BIT0;
    P5REN |= BIT1;
    P5REN |= BIT2;
    P5REN |= BIT3;
    P5REN |= BIT4;
    P5REN |= BIT5;
    P5REN |= BIT6;
    P5REN |= BIT7;

    P5OUT &= ~BIT0;
    P5OUT &= ~BIT1;
    P5OUT &= ~BIT2;
    P5OUT &= ~BIT3;
    P5OUT &= ~BIT4;
    P5OUT &= ~BIT5;
    P5OUT &= ~BIT6;
    P5OUT &= ~BIT7;

    // Port 6
    P6DIR &= ~DISTANCE_RIGHT;   // IN
    P6DIR &= ~DISTANCE_LEFT;    // IN
    P6DIR &= ~DISTANCE_FRONT;   // IN
    P6DIR &= ~VBAT_MEASURE;     // IN
    P6DIR |= DISTANCE_LEFT_EN;  // OUT
    P6DIR &= ~BIT5;             // IN
    P6DIR &= ~BIT6;             // IN
    P6DIR &= ~BIT7;             // IN

    P6REN |= BIT5;
    P6REN |= BIT6;
    P6REN |= BIT7;

    P6OUT &= ~BIT5;
    P6OUT &= ~BIT6;
    P6OUT &= ~BIT7;

    // Port 7
    P7DIR &= ~XT2IN;            // IN
    P7DIR |= XT2OUT;            // OUT
    P7DIR &= ~BIT4;             // IN
    P7DIR &= ~BIT5;             // IN
    P7DIR &= ~BIT6;             // IN
    P7DIR &= ~BIT7;             // IN

    P7REN |= BIT4;
    P7REN |= BIT5;
    P7REN |= BIT6;
    P7REN |= BIT7;

    P7OUT &= ~BIT4;
    P7OUT &= ~BIT5;
    P7OUT &= ~BIT6;
    P7OUT &= ~BIT7;

    // Port 8
    P8DIR |= LCD_BL;            // OUT
    P8DIR |= LCD_SPI_CS;        // OUT
    P8DIR |= UART_TXD_AUX;      // OUT
    P8DIR &= ~UART_RXD_AUX;     // IN
    P8DIR |= LCD_SPI_CLK;       // OUT
    P8DIR |= LCD_SPI_MOSI;      // OUT
    P8DIR &= ~LCD_SPI_MISO;     // IN
    P8DIR |= LCD_DATACMD;       // OUT

    // Port 9
    P9DIR |= LCD_RESET;         // OUT
    P9DIR &= ~BIT1;             // IN
    P9DIR &= ~BIT2;             // IN
    P9DIR &= ~BIT3;             // IN
    P9DIR &= ~BIT4;             // IN
    P9DIR &= ~BIT5;             // IN
    P9DIR &= ~BIT6;             // IN
    P9DIR |= DISTANCE_RIGHT_EN; // OUT

    P9REN |= BIT1;
    P9REN |= BIT2;
    P9REN |= BIT3;
    P9REN |= BIT4;
    P9REN |= BIT5;
    P9REN |= BIT6;

    P9OUT &= ~BIT1;
    P9OUT &= ~BIT2;
    P9OUT &= ~BIT3;
    P9OUT &= ~BIT4;
    P9OUT &= ~BIT5;
    P9OUT &= ~BIT6;

}
