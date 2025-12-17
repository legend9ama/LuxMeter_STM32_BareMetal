#include "stm32f0xx.h"

// Peripherals
#include "GPIO/gpio.h"
#include "I2C/i2c.h"
#include "SysTick/SysTick.h"
//Modules
#include "BH1750/bh1750.h"



volatile float lux = 0.0;
volatile uint16_t raw_data = 0;

int main(void) {
    GPIO_Init();
    I2C1_Init();
    SysTickDelayMS(10);

    // Power On
    BH1750_Write(0x01);
    SysTickDelayMS(10);
    
    // Continuos High Res Mode
    BH1750_Write(0x10);
    SysTickDelayMS(180);

    while (1) {
        raw_data = BH1750_Read();
        lux = (float)raw_data / 1.2f;
        GPIOB->ODR ^= (1U << 1);
        
        SysTickDelayMS(500);
    }
}