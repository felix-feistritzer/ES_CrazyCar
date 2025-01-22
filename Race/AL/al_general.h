#ifndef _AL_GENENAL_H_
#define _AL_GENERAL_H_

typedef enum State
{
    Data,
    CCW,
    CW,
    Stop,
    Test
}State_t;

void AL_Init(void);
void AL_CCW(void);
void AL_CW(void);
void AL_Stop(void);
void AL_Test(void);

#endif
