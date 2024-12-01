#ifndef _DRIVER_LCD_H_
#define _DRIVER_LCD_H_

#include <stdint.h>
#include "hal_gpio.h"
#include "hal_usciB1.h"

// Commands LCD Display
#define CMD_LCD_RESET       0xE2
#define CMD_LCD_BIAS        0xA3
#define CMD_ADC_SEL_NORMAL  0xA0
#define CMD_COMMON_REVERSE  0xC8
#define CMD_RES_RATIO       0x24
#define CMD_ELEC_VOL_MODE   0x81
#define CMD_ELEC_VOL_VALUE  0x0F
#define CMD_POWER_CONT      0x2F
#define CMD_DISPLAY_ON      0xAF

#define SET_PAGE            0xB0    // first Page
#define LAST_PAGE           0xB7    // last Page
#define MSN_COL_ADDR        0x10
#define LSN_COL_ADDR        0x00
#define LCD_MAX_COL         0x80    // 128

// Makros
#define LCD_DATA (P8OUT |= LCD_DATACMD)
#define LCD_COMMAND (P8OUT &= ~LCD_DATACMD)

void Driver_LCD_WriteCommand(uint8_t *data, uint8_t len);
void Driver_LCD_SetPosition(uint8_t page, uint8_t column);
void Driver_LCD_Init(void);
void Driver_LCD_Clear(void);
void Driver_LCD_WriteText (uint8_t *text, uint8_t len, uint8_t page, uint8_t col);
void Driver_LCD_DrawBar(uint16_t value, uint16_t maxValue, uint8_t width, uint8_t page, uint8_t startCol);

#endif
