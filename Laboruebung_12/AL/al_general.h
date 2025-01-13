#ifndef _AL_GENENAL_H_
#define _AL_GENERAL_H_

typedef enum State
{
    Data,
    Start,
    CCW,
    CW,
    Stop
}State_t;

void AL_Init(void);

#endif
