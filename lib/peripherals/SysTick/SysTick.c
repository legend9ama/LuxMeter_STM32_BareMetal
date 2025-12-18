#include "SysTick.h"

static volatile uint32_t ms_ticks = 0;

void SysTick_Init(void) {
    if(SysTick_Config(SystemCoreClock/1000)){
        while(1);
    }
    NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
}

void SysTick_Handler(void) {
    ms_ticks++;
}

void SysTickDelayMS(volatile uint32_t delay) {
    uint32_t start = ms_ticks;
    while((ms_ticks-start) < delay){}
}

uint32_t GetTick(void) {
    return ms_ticks;
}