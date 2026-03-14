#pragma once
#include "stm32f0xx.h"
#include "SysTick.h"

void ADC_Init(void);
uint16_t ADC_Read_Value(void);
