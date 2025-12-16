#include <stdint.h>
#include <stm32f0xx.h>

#define CYCLE_PER_MS 8000
#define CTRL_ENABLE (1U<<0)
#define CTRL_CLKSRC (1U<<2)
#define CTRL_COUNTFLAG (1U<<16)

void SysTickDelayMS(volatile uint32_t delay) {
    SysTick->LOAD = CYCLE_PER_MS - 1;

    SysTick->VAL = 0;

    SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

    for(int i = 0; i < delay; i++){
        while((SysTick->CTRL & CTRL_COUNTFLAG) == 0){}
    }
    SysTick->CTRL = 0;
}

int main(void) {
    RCC->AHBENR |= (1U<<18);
    GPIOB->MODER |= (1U<<2);
    GPIOB->MODER &= ~(1U<<3);

    while (1) {
        //Blink
        GPIOB->ODR ^= (1U<<1);
        SysTickDelayMS(500);
    }
}