#include "hal_general.h"
#include "hal_pmm.h"
#include "hal_wdt.h"
#include "hal_gpio.h"

ButtonCom buttonCom;

void HAL_Init(void)
{
    HAL_PMM_Init();
    HAL_Wdt_Init();
    HAL_GPIO_Init();
}
