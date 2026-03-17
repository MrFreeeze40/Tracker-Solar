#include "adc.h"

bool ADC_overrun(ADC_TypeDef *p_adc) {
    return (p_adc->SR & ADC_SR_OVR) != 0;
}

bool ADC_conversion_started(ADC_TypeDef *p_adc) {
    return (p_adc->SR & ADC_SR_STRT) != 0;
}

bool ADC_conversion_completed(ADC_TypeDef *p_adc) {
    return (p_adc->SR & ADC_SR_EOC) != 0;
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

void set_alignment(ADC_TypeDef *p_adc, bool right_align) {
    if (right_align) {
        p_adc->CR2 |= ADC_CR2_ALIGN;
    } else {
        p_adc->CR2 &= ~ADC_CR2_ALIGN;
    }
}
