#ifndef _DRIVER_AKTORIK_H_
#define _DRIVER_AKTORIK_H_

#include <stdint.h>

#define STEERING_LEFT_MAX   0x0ABE  // 2750
#define STEERING_CENTER     0x0EA6  // 3750
#define STEERING_RIGHT_MAX  0x128E  // 4750

void Driver_SetSteering(int8_t value);
void Driver_SteeringInit(void);

#endif
