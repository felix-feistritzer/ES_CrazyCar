#ifndef _AL_TEST_H_
#define _AL_TEST_H_

#include <stdint.h>

typedef enum DriveState_Test
{
    INIT_T,
    START_T,
    LEFT_T,
    STOP_T
} DriveState_Test_t;

void AL_Algorithm_Test(void);
int16_t AL_Regler_right_Test(uint16_t left_dist);
void AL_SetSpeed_Test(int16_t target_speed);

#endif
