#pragma once
#include <stm32f0xx.h>

#define CYCLE_PER_MS 8000 // At 8 MHz 0.001s / (1/8000000)s = 8000 cycles

void SysTickDelayMS(volatile uint32_t delay);