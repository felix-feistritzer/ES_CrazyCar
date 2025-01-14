#ifndef _AL_ALGORITHM_H_
#define _AL_ALGORITHM_H_

#include <stdint.h>

#define RIGHT 0
#define LEFT  1
#define FRONT 2
#define VBAT  3

typedef enum DriveState
{
    INIT,
    START,
    T1,
    S2,
    T2,
    S3,
    T3,
    S4,
    T4,
    S5,
    T5,
    S6,
    T6,
    S7,
    T7,
    S8,
    T8,
    S1
} DriveState_t;

void AL_Algorithm(void);
int16_t AL_Regler(void);
void AL_Recovery(void);

#endif
