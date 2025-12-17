#include "gpio.h"

void GPIO_Init(void) {
    // RCC FOR GPIOA GPIOB GPIOF
    RCC->AHBENR |= (1U << 17) | (1U << 18) | (1U << 22);
    // -----------------------------------
    // MODER
    // -----------------------------------
    // RESET MODE FOR PINS PA
    GPIOA->MODER &= ~((3U) | (3U << 2) | (3U << 4) | (3U << 6) | 
                    (3U << 8) | (3U << 10) | (3U << 12) | 
                    (3U << 14) | (3U << 18) | (3U << 20));
    // SET MODE FOR PINS PA
    GPIOA->MODER |= ((3U) | (1U << 2) | (1U << 4) | (1U << 6) |
                    (1U << 8) | (2U << 10) | (2U << 12) | 
                    (2U << 14) | (2U << 18) | (2U << 20));
    // CLEAR AND SET PB1 TO OUTPUT
    GPIOB->MODER &= ~(3U << 2);
    GPIOB->MODER |= (1U << 2);
    // SET PF0 AND PF1 TO INPUT
    GPIOF->MODER &= ~((3U) | (3U << 2));
    // -----------------------------------
    // OTYPER
    // -----------------------------------
    // RESET OUTPUT TYPE FOR GPIOA
    GPIOA->OTYPER &= ~((1U << 1) | (1U << 2) | (1U << 3) | 
                   (1U << 4) | (1U << 5) | (1U << 6) | 
                   (1U << 7) | (1U << 9) | (1U << 10));
    // SET PA9 AND PA10 TO OPEN-DRAIN
    GPIOA->OTYPER |= (1U << 9 | 1U << 10);
    // -----------------------------------
    // PUPDR
    // -----------------------------------
    // SET PULL-UP RESISTORS FOR PA4, PF0 AND PF1
    GPIOA->PUPDR |= (1U << 8);
    GPIOF->PUPDR |= ((1U) | (1U << 2));
    // SET SPEED FOR GPIOA
    GPIOA->OSPEEDR &= ~((3U << 2) | (3U << 4) | (3U << 6));
    GPIOA->OSPEEDR |= ((3U << 8) | (3U << 10) | (3U << 12) | (3U << 14) | (3U << 18) | (3U << 20));
    // -----------------------------------
    // AF
    // -----------------------------------
    // SET AF FOR PA5 PA6 PA7 PA9 AND PA10
    GPIOA->AFR[0] &= ~((15U << 20) | (15U << 24) | (15U << 28));
    GPIOA->AFR[1] &= ~((15U << 4) | (15U << 8));
    GPIOA->AFR[1] |= ((4U << 4) | (4U << 8));
    // -----------------------------------
    // BSRR
    // -----------------------------------
    // SET BH1750(ACTIVE) AND SD_CS(IDLE)
    GPIOA->BSRR = (1U << 2) | (1U << 4);
}