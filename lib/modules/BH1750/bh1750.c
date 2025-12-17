#include "bh1750.h"

void BH1750_Write(uint8_t cmd) {
    while(I2C1->ISR & I2C_ISR_BUSY);

    I2C1->CR2 = (BH1750_ADDR) | (1U << 16) | (1U << 25) | (1U << 13);

    while(!(I2C1->ISR & ((1U << 1) | (1U << 4))));

    if (I2C1->ISR & I2C_ISR_NACKF) {
        I2C1->ICR |= I2C_ICR_NACKCF;
        return;
    }

    I2C1->TXDR = cmd;

    while(!(I2C1->ISR & I2C_ISR_STOPF));
    I2C1->ICR |= I2C_ICR_STOPCF;
}

uint16_t BH1750_Read(void) {
    uint8_t data[2] = {0, 0};

    while(I2C1->ISR & I2C_ISR_BUSY);
    
    I2C1->CR2 = (BH1750_ADDR) | (2 << I2C_CR2_NBYTES_Pos) | I2C_CR2_RD_WRN | I2C_CR2_AUTOEND | I2C_CR2_START;
    
    while(!(I2C1->ISR & (I2C_ISR_RXNE | I2C_ISR_NACKF)));
    if (I2C1->ISR & I2C_ISR_NACKF) {
        I2C1->ICR |= I2C_ICR_NACKCF;
        return 0;
    }
    data[0] = I2C1->RXDR;

    while(!(I2C1->ISR & I2C_ISR_RXNE));
    data[1] = I2C1->RXDR;

    while(!(I2C1->ISR & I2C_ISR_STOPF));
    I2C1->ICR |= I2C_ICR_STOPCF;
    
    return ((data[0] << 8) | data[1]);
}