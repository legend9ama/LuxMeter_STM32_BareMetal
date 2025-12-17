#pragma once
#include "stm32f0xx.h"
#define BH1750_ADDR (0x23 << 1)

void BH1750_Write(uint8_t cmd); //send command

uint16_t BH1750_Read(void); //read value