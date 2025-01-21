#ifndef _AL_TEST_H_
#define _AL_TEST_H_

#include <stdint.h>

typedef enum DriveState_Test
{
    INIT_T,
    START_T,
    STOP_T
} DriveState_Test_t;

void AL_Algorithm_Test(void);
int16_t AL_Regler_Test(void);
void AL_SetSpeed_Test(int16_t target_speed);

#endif
