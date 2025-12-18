#include "ssd1306.h"

static uint8_t SSD1306_Buffer[1024];

const uint8_t Font[][5] = {
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E}, // 9
    {0x00, 0x36, 0x36, 0x00, 0x00}, // :
    {0x00, 0x00, 0x00, 0x00, 0x00}, // Space
    {0x7F, 0x40, 0x40, 0x40, 0x00}, // L
    {0x3E, 0x40, 0x40, 0x3E, 0x00}, // u
    {0x63, 0x14, 0x08, 0x14, 0x63}, // x
    {0x00, 0x60, 0x60, 0x00, 0x00}  // .
};

static int GetFontIndex(char c){
    if (c >= '0' && c <= '9') return c - '0';
    if (c == ':') return 10;
    if (c == ' ') return 11;
    if (c == 'L') return 12;
    if (c == 'u') return 13;
    if (c == 'x') return 14;
    if (c == '.') return 15;
    return 11;
}

void SSD1306_DrawChar(char c, uint8_t x, uint8_t y, uint8_t color){
    int idx = GetFontIndex(c);

    for (uint8_t i = 0; i < 5; i++){
        uint8_t line = Font[idx][i];
        for (uint8_t j = 0; j < 7; ++j){
            if(line & (1 << j)){
                SSD1306_DrawPixel(x + i, y + j, color);
            }
            else {
                SSD1306_DrawPixel(x + i, y + j, !color);
            }
        }
    }
}

static void ssd1306_WriteCommand(uint8_t cmd) {
    while(I2C1->ISR & I2C_ISR_BUSY);

    I2C1->CR2 = (SSD1306_I2C_ADDR) | (2 << 16) | I2C_CR2_AUTOEND | I2C_CR2_START;
    
    while(!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = 0x00;

    while(!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = cmd;

    while(!(I2C1->ISR & I2C_ISR_STOPF));
    I2C1->ICR |= I2C_ICR_STOPCF;
}

void SSD1306_DrawString(const char* str, uint8_t x, uint8_t y, uint8_t color) {
    while (*str) {
        SSD1306_DrawChar(*str, x, y, color);
        x+=6;
        str++;
    }
}

static void ssd1306_WriteData(uint8_t* data, uint8_t count) {
    while(I2C1->ISR & I2C_ISR_BUSY);

    I2C1->CR2 = (SSD1306_I2C_ADDR) | ((count + 1) << 16) | I2C_CR2_AUTOEND | I2C_CR2_START;

    while(!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = 0x40;

    for (uint8_t i = 0; i < count; i++) {
        while(!(I2C1->ISR & I2C_ISR_TXIS));
        I2C1->TXDR = data[i];
    }

    while(!(I2C1->ISR & I2C_ISR_STOPF));
    I2C1->ICR |= I2C_ICR_STOPCF;
}

void SSD1306_Init(void) {
    for(volatile int i=0; i<100000; i++); 

    ssd1306_WriteCommand(0xAE); // Display OFF (sleep mode)
    
    ssd1306_WriteCommand(0x20); // Set Memory Addressing Mode
    ssd1306_WriteCommand(0x00); // 00 = Horizontal Addressing Mode

    ssd1306_WriteCommand(0xB0); // Set Page Start Address for Page Addressing Mode

    ssd1306_WriteCommand(0xC8); // Set COM Output Scan Direction
    ssd1306_WriteCommand(0x00); // Set Low Column Address
    ssd1306_WriteCommand(0x10); // Set High Column Address

    ssd1306_WriteCommand(0x40); // Set Start Line Address

    ssd1306_WriteCommand(0x81); // Set Contrast Control
    ssd1306_WriteCommand(0xFF); // Max contrast

    ssd1306_WriteCommand(0xA1); // Set Segment Re-map
    ssd1306_WriteCommand(0xA6); // Set Normal Display

    ssd1306_WriteCommand(0xA8); // Set Multiplex Ratio
    ssd1306_WriteCommand(0x3F); // (64-1)

    ssd1306_WriteCommand(0xA4); // Output follows RAM content

    ssd1306_WriteCommand(0xD3); // Set Display Offset
    ssd1306_WriteCommand(0x00); // Not offset

    ssd1306_WriteCommand(0xD5); // Set Display Clock Divide Ratio/Oscillator Frequency
    ssd1306_WriteCommand(0xF0); // Set Divide Ratio

    ssd1306_WriteCommand(0xD9); // Set Pre-charge Period
    ssd1306_WriteCommand(0x22); 

    ssd1306_WriteCommand(0xDA); // Set COM Pins Hardware Configuration
    ssd1306_WriteCommand(0x12); 

    ssd1306_WriteCommand(0xDB); // Set VCOMH Deselect Level
    ssd1306_WriteCommand(0x20); // 0.77xVcc

    ssd1306_WriteCommand(0x8D); // Charge Pump Setting
    ssd1306_WriteCommand(0x14); // Enable Charge Pump

    ssd1306_WriteCommand(0xAF); // Display ON

    SSD1306_Fill(0);
    SSD1306_UpdateScreen();
}

void SSD1306_Fill(uint8_t color) {
    uint8_t byte = (color) ? 0xFF : 0x00;
    for(uint16_t i = 0; i < sizeof(SSD1306_Buffer); i++) {
        SSD1306_Buffer[i] = byte;
    }
}

void SSD1306_DrawPixel(uint8_t x, uint8_t y, uint8_t color) {
    if (x >= 128 || y >= 64) return;

    if (color) {
        SSD1306_Buffer[x + (y / 8) * 128] |= (1 << (y % 8));
    } else {
        SSD1306_Buffer[x + (y / 8) * 128] &= ~(1 << (y % 8));
    }
}

void SSD1306_UpdateScreen(void) {
    for (uint8_t page = 0; page < 8; page++) {
        ssd1306_WriteCommand(0xB0 + page); // Page Start Address
        ssd1306_WriteCommand(0x00);        // Lower Column Start Address
        ssd1306_WriteCommand(0x10);        // Higher Column Start Address

        ssd1306_WriteData(&SSD1306_Buffer[page * 128], 128);
    }
}