#ifndef _HAL_UCS_H_
#define _HAL_UCS_H_

#include <msp430.h>

#define XTAL_FREQU  20000000    // 20 MHz
#define MCLK_FREQU  20000000    // 20 MHz
#define SMCLK_FREQU 2500000     // 2.5 MHz

void HAL_UCS_init(void);

#endif
