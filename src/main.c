#include <stdio.h>
#include "stm32f0xx.h"
// Peripherals
#include "GPIO/gpio.h"
#include "I2C/i2c.h"
#include "RCC/rcc.h"
#include "SysTick/SysTick.h"
//Modules
#include "BH1750/bh1750.h"
#include "OLED/ssd1306.h"


volatile float lux = 0.0;
volatile uint16_t raw_data = 0;

int main(void) {
    SystemClock_Config_48MHz();
    SysTick_Init();

    GPIO_Init();
    I2C1_Init();
    SysTickDelayMS(100);

    SSD1306_Init();
    SSD1306_Fill(0);
    SSD1306_UpdateScreen();
    // Power On
    BH1750_Write(0x01);
    SysTickDelayMS(10);
    
    // Continuos High Res Mode
    BH1750_Write(0x10);
    SysTickDelayMS(180);

    char msg[16];
    int prev_lux = -1;

    while (1) {
        raw_data = BH1750_Read();
        lux = (float)raw_data / 1.2f;

        int whole_lux = (int)lux;
        int dec_lux = (int)((lux-whole_lux) * 10);
        if (dec_lux < 0) dec_lux = -dec_lux;
        if(whole_lux != prev_lux){
            SSD1306_Fill(0);
            sprintf(msg, "Lux: %d.%d", whole_lux, dec_lux);
            SSD1306_DrawString(msg, 5, 25, 1);
            SSD1306_UpdateScreen();

            prev_lux = whole_lux;
        }

        SysTickDelayMS(150);
    }
}