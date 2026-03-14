#include "ADC/adc.h"
#include "stm32f0xx.h"

uint8_t Get_Battery_Percentage(void) {
    uint16_t adc_value = ADC_Read_Value();
    float v_bat = ((adc_value * 3.3f) / 4095.0f) * 2.0f;
    if (v_bat >= 4.2f) return 100;
    if (v_bat <= 3.0f) return 0;

    return (uint8_t)((v_bat - 3.0f) * 100.0f / (4.2f - 3.0f));
}

