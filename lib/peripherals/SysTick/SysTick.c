#include "SysTick.h"

void SysTick_Init(void);

void SysTickDelayMS(volatile uint32_t delay) {
    SysTick->LOAD = CYCLE_PER_MS - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;

    for(int i = 0; i < delay; i++){
        while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0){}
    }
    SysTick->CTRL = 0;
}