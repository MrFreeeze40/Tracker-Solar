#include "adc.h"
#include "stm32f446xx.h"

bool ADC_overrun(ADC_TypeDef *p_adc) {
    return (p_adc->SR & ADC_SR_OVR) != 0;
}

bool ADC_conversion_started(ADC_TypeDef *p_adc) {
    return (p_adc->SR & ADC_SR_STRT) != 0;
}

bool ADC_conversion_completed(ADC_TypeDef *p_adc) {
    return (p_adc->SR & ADC_SR_EOC) != 0;
}

void ADC_clear_overrun_flag(ADC_TypeDef *p_adc) {
    p_adc->SR = ~ADC_SR_OVR;
}

void ADC_clear_watchdog_flag(ADC_TypeDef *p_adc) {
    p_adc->SR = ~ADC_SR_AWD;
}

void ADC_clear_end_of_conversion_flag(ADC_TypeDef *p_adc) {
    p_adc->SR = ~ADC_SR_EOC;
}

void ADC_clear_start_flag(ADC_TypeDef *p_adc) {
    p_adc->SR = ~ADC_SR_STRT;
}

bool ADC_is_watchdog_triggered(ADC_TypeDef *p_adc) {
    return (p_adc->SR & ADC_SR_AWD) != 0;
}

void ADC_enable_overrun_interrupt(ADC_TypeDef *p_adc) {
    p_adc->CR1 |= ADC_CR1_OVRIE;
}
void ADC_disable_overrun_interrupt(ADC_TypeDef *p_adc) {
    p_adc->CR1 &= ~ADC_CR1_OVRIE;
}

void ADC_configure_analog_watchdog(ADC_TypeDef *p_adc, enum ADC_analog_watchdog_channel_e channel_selection) {
    p_adc->CR1 &= ~ADC_CR1_AWDEN;
    p_adc->CR1 &= ~ADC_CR1_JAWDEN;
    p_adc->CR1 &= ~ADC_CR1_AWDSGL;
    p_adc->CR1 |= (channel_selection << 23);
}

void ADC_set_resolution(ADC_TypeDef *p_adc, enum ADC_resolution_e resolution) {
    p_adc->CR1 &= ~ADC_CR1_RES;
    p_adc->CR1 |= (resolution << 24);
}

void ADC_enable(ADC_TypeDef *p_adc) {
    p_adc->CR2 |= ADC_CR2_ADON;
}

void ADC_disable(ADC_TypeDef *p_adc) {
    p_adc->CR2 &= ~ADC_CR2_ADON;
}

void ADC_start_conversion(ADC_TypeDef *p_adc) {
    p_adc->CR2 |= ADC_CR2_SWSTART;
}

void ADC_stop_conversion(ADC_TypeDef *p_adc) {
    p_adc->CR2 &= ~ADC_CR2_SWSTART;
}

void ADC_enable_watchdog(ADC_TypeDef *p_adc, uint16_t low_threshold, uint16_t high_threshold) {
    p_adc->CR1 |= ADC_CR1_AWDEN;
    p_adc->HTR = high_threshold;
    p_adc->LTR = low_threshold;
}

void ADC_disable_watchdog(ADC_TypeDef *p_adc) {
    p_adc->CR1 &= ~ADC_CR1_AWDEN;
}

void ADC_enable_watchdog_interrupt(ADC_TypeDef *p_adc) {
    p_adc->CR1 |= ADC_CR1_AWDIE;
}

void ADC_disable_watchdog_interrupt(ADC_TypeDef *p_adc) {
    p_adc->CR1 &= ~ADC_CR1_AWDIE;
}

uint16_t ADC_get_conversion_value(ADC_TypeDef *p_adc) {
    return p_adc->DR;
}

void ADC_set_alignment(ADC_TypeDef *p_adc, bool right_align) {
    if (right_align) {
        p_adc->CR2 &= ~ADC_CR2_ALIGN;
    } else {
        p_adc->CR2 |= ADC_CR2_ALIGN;
    }
}

void ADC_enable_scan_mode(ADC_TypeDef *p_adc) {
    p_adc->CR1 |= ADC_CR1_SCAN;
}
void ADC_disable_scan_mode(ADC_TypeDef *p_adc) {
    p_adc->CR1 &= ~ADC_CR1_SCAN;
}

void ADC_enable_continuous_mode(ADC_TypeDef *p_adc) {
    p_adc->CR2 |= ADC_CR2_CONT;
}
void ADC_disable_continuous_mode(ADC_TypeDef *p_adc) {
    p_adc->CR2 &= ~ADC_CR2_CONT;
}

void ADC_select_channel(ADC_TypeDef *p_adc, uint8_t channel, uint8_t rank) {
    if (rank <= 6) {
        p_adc->SQR3 &= ~(0x1F << ((rank - 1) * 5));
        p_adc->SQR3 |= (channel << ((rank - 1) * 5));
    } else if (rank <= 12) {
        p_adc->SQR2 &= ~(0x1F << ((rank - 7) * 5));
        p_adc->SQR2 |= (channel << ((rank - 7) * 5));
    } else if (rank <= 16) {
        p_adc->SQR1 &= ~(0x1F << ((rank - 13) * 5));
        p_adc->SQR1 |= (channel << ((rank - 13) * 5));
    }
}

void ADC_set_sequence_length(ADC_TypeDef *p_adc, uint8_t length) {
    p_adc->SQR1 &= ~ADC_SQR1_L;
    p_adc->SQR1 |= ((length - 1) << 20);
}
