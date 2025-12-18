#include "rcc.h"

void SystemClock_Config_48MHz(void){
    RCC->CR |= 0x1U;
    while (!(RCC->CR & (0x1U << 1)));

    FLASH->ACR |= (0x1U << 4) | (0x1U);

    RCC->CFGR &= ~((0xFU << 18) | (0xFU << 16));
    RCC->CFGR |= 0x00280000U;

    RCC->CR |= (0x1U << 24);
    while (!(RCC->CR & (0x1U << 25)));

    RCC->CFGR &= ~(0x3U);
    RCC->CFGR |= (0x2U);
    
    while ((RCC->CFGR & (0x3U << 2)) != (0x8U));

    SystemCoreClockUpdate();
}
