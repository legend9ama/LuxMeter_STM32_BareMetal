#pragma once
#include <stm32f0xx.h>

void SysTick_Init(void);
void SysTick_Handler(void);
void SysTickDelayMS(volatile uint32_t delay);
uint32_t GetTick(void);