#ifndef _DRIVER_AKTORIK_H_
#define _DRIVER_AKTORIK_H_

#include <stdint.h>

#define STEERING_LEFT_MAX   0x0ABE  // 2750 // 1,1ms
#define STEERING_CENTER     0x0EA6  // 3750 // 1,5ms
#define STEERING_RIGHT_MAX  0x128E  // 4750 // 1,9ms
#define STEERING_OFFSET     50

#define THROTTLE_MAXRPW     0x09C4  // 2500 // 1000us
#define THROTTLE_MINRPW     0x1388  // 5000 // 2000us
#define THROTTLE_MAXBREAK   0x17ED  // 6125 // 2500us
#define THROTTLE_MINFPW     0x1D4C  // 7500 // 3000us
#define THROTTLE_MAXFPW     0x2710  // 10000 // 4000us

void Driver_SetSteering(int8_t value);
void Driver_SteeringInit(void);
void Driver_SetThrottle(int8_t value);
void Driver_ThrottleInit(void);
void pwmCycles(uint16_t pwm, uint16_t cycles);

#endif
