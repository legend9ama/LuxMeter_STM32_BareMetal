#include "stm32f0xx.h"
#include "SysTick.h"

void ADC_Init(void){
    RCC->APB2ENR |= RCC_APB2ENR_ADCEN;

    if ((ADC1->CR & ADC_CR_ADEN) != 0) ADC1->CR |= ADC_CR_ADDIS;
    while((ADC1->CR & ADC_CR_ADEN) != 0);
    ADC1->CR |= ADC_CR_ADCAL;
    while ((ADC1->CR & ADC_CR_ADCAL) != 0);
    
    ADC1->CR |= ADC_CR_ADEN;
    while (!(ADC1->ISR & ADC_ISR_ADRDY));
    ADC1->CHSELR = ADC_CHSELR_CHSEL0;
    ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2;
}

uint16_t ADC_Read_Value(void){
    uint16_t result;
    GPIOA->BSRR = (1U << 3);
    SysTickDelayMS(10);

    ADC1-> CR |= ADC_CR_ADSTART;
    while (!(ADC1->ISR & ADC_ISR_EOC));
    result = (uint16_t)ADC1->DR;

    GPIOA->BSRR = (0U << 3);
    return result;
}
