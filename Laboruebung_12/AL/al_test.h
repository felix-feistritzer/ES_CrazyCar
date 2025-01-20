#ifndef _AL_TEST_H_
#define _AL_TEST_H_

#include <stdint.h>

typedef enum DriveState_Test
{
    INIT_T,
    START_T,
    T1_T,
    S2_T,
    T2_T,
    S3_T,
    STOP_T
} DriveState_Test_t;

void AL_Algorithm_Test(void);
//void AL_SetSpeed(int16_t target_speed);
void AL_Break(int16_t target_speed);

#endif
