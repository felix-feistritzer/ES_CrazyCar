#include "hal_general.h"
#include "hal_pmm.h"
#include "hal_wdt.h"
#include "hal_gpio.h"
#include "hal_ucs.h"
#include "hal_timerB0.h"

ButtonCom buttonCom;

void HAL_Init(void)
{
    HAL_PMM_Init();
    HAL_Wdt_Init();
    HAL_GPIO_Init();
    HAL_UCS_Init();
    HAL_TimerB0_Init();
}
