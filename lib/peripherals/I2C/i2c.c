#include "stm32f0xx.h"

void I2C1_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;

    GPIOA->MODER &= ~((3U << 18) | (3U << 20)); // RESET MODE
    GPIOA->MODER |= ((2U << 18) | (2U << 20));  // AF Mode
    GPIOA->OTYPER |= (1U << 9) | (1U << 10);    // Open-Drain
    GPIOA->OSPEEDR |= (3U << 18) | (3U << 20);  // High Speed
    
    GPIOA->AFR[1] &= ~((0xF << 4) | (0xF << 8)); 
    GPIOA->AFR[1] |= ((4U << 4) | (4U << 8)); 

    I2C1->CR1 &= ~I2C_CR1_PE;
    
    I2C1->TIMINGR = 0x00901850; 
    
    I2C1->CR1 |= I2C_CR1_PE;
}