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

#endif
