#pragma once
#include "stm32f0xx.h"

#define SSD1306_I2C_ADDR (0x3C << 1) 

void SSD1306_DrawChar(char c, uint8_t x, uint8_t y, uint8_t color);
void SSD1306_DrawString(const char* c, uint8_t x, uint8_t y, uint8_t color);

void SSD1306_Init(void);
void SSD1306_Fill(uint8_t color);
void SSD1306_UpdateScreen(void);
void SSD1306_DrawPixel(uint8_t x, uint8_t y, uint8_t color);