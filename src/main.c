#include <registers.h>

void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");
    }
}

int main(void) {
    RCC_AHBENR |= (1U<<18);
    GPIOB_MODER |= (1U<<2);
    
    GPIOB_MODER &= ~(1U<<3);

    while (1) {
        //Blink
        GPIOB_ODR ^= (1U<<1);
        delay(200000);
    }
}