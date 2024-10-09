#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_

#include <msp430.h>

// Port J

// Port 1
#define RPM_SENSOR          BIT3
#define RPM_SENSOR_DIR      BIT4
#define I2C_INT_MOTION      BIT5
#define START_BUTTON        BIT6
#define STOP_BUTTON         BIT7

// Port 2
#define DEBUG_TXD           BIT0
#define DEBUG_RXD           BIT1
#define AUX_PIN_1           BIT2
#define AUX_PIN_2           BIT3
#define AUX_PIN_3           BIT4
#define AUX_PIN_4           BIT5
#define I2C_SDA_MOTION      BIT6
#define I2C_SCL_MOTION      BIT7

// Port 3
#define THROTTLE            BIT2
#define STEERING            BIT3
#define SMCLK               BIT4
#define DISTANCE_FRONT_EN   BIT7

// Port 4
#define LINE_FOLLOW_2       BIT3
#define LINE_FOLLOW_1       BIT4
#define LINE_FOLLOW_3       BIT5
#define LINE_FOLLOW_4       BIT6
#define LINE_FOLLOW_5       BIT7

// Port 5

// Port 6
#define DISTANCE_RIGHT      BIT0
#define DISTANCE_LEFT       BIT1
#define DISTANCE_FRONT      BIT2
#define VBAT_MEASURE        BIT3
#define DISTANCE_LEFT_EN    BIT4

// Port 7
#define XT2IN               BIT2
#define XT2OUT              BIT3

// Port 8
#define LCD_BL              BIT0
#define LCD_SPI_CS          BIT1
#define UART_TXD_AUX        BIT2
#define UART_RXD_AUX        BIT3
#define LCD_SPI_CLK         BIT4
#define LCD_SPI_MOSI        BIT5
#define LCD_SPI_MISO        BIT6
#define LCD_DATACMD         BIT7

// Port 9
#define LCD_RESET           BIT0
#define DISTANCE_RIGHT_EN   BIT7

void HAL_GPIO_Init(void);

#endif
