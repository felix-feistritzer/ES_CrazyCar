#ifndef _DRIVER_SENSOR_H_
#define _DRIVER_SENSOR_H_

#include <stdint.h>

uint16_t Driver_GetFrontDist(uint16_t adc_value);
uint16_t Driver_GetLeftDist(uint16_t adc_value);
uint16_t Driver_GetRightDist(uint16_t adc_value);

#endif
