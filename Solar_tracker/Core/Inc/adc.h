#ifndef __ADC_H__
#define __ADC_H__
#include "common.h"
#include "stm32f446xx.h"
#include <stdbool.h>
#include <stdint.h>

bool ADC_overrun(ADC_TypeDef *p_adc);

bool ADC_conversion_started(ADC_TypeDef *p_adc);

bool ADC_conversion_completed(ADC_TypeDef *p_adc);

void ADC_clear_overrun_flag(ADC_TypeDef *p_adc);
void ADC_clear_watchdog_flag(ADC_TypeDef *p_adc);
void ADC_clear_end_of_conversion_flag(ADC_TypeDef *p_adc);
void ADC_clear_start_flag(ADC_TypeDef *p_adc);

bool ADC_is_watchdog_triggered(ADC_TypeDef *p_adc);

void ADC_enable_overrun_interrupt(ADC_TypeDef *p_adc);
void ADC_disable_overrun_interrupt(ADC_TypeDef *p_adc);

enum ADC_analog_watchdog_channel_e {
    ADC_ANALOG_WATCHDOG_SINGLE_REGULAR_CHANNEL = 0b00,
    ADC_ANALOG_WATCHDOG_ALL_REGULAR_CHANNELS = 0b01,
    ADC_ANALOG_WATCHDOG_SINGLE_INJECTED_CHANNEL = 0b10,
    ADC_ANALOG_WATCHDOG_ALL_INJECTED_CHANNELS = 0b11
};

void ADC_configure_analog_watchdog(ADC_TypeDef *p_adc, enum ADC_analog_watchdog_channel_e channel_selection);

enum ADC_resolution_e {
    ADC_RESOLUTION_12_BIT = 0b00,
    ADC_RESOLUTION_10_BIT = 0b01,
    ADC_RESOLUTION_8_BIT = 0b10,
    ADC_RESOLUTION_6_BIT = 0b11
};

void ADC_set_resolution(ADC_TypeDef *p_adc, enum ADC_resolution_e resolution);

void ADC_enable(ADC_TypeDef *p_adc);

void ADC_disable(ADC_TypeDef *p_adc);

void ADC_start_conversion(ADC_TypeDef *p_adc);

void ADC_stop_conversion(ADC_TypeDef *p_adc);

void ADC_enable_watchdog(ADC_TypeDef *p_adc, uint16_t low_threshold, uint16_t high_threshold);
void ADC_disable_watchdog(ADC_TypeDef *p_adc);

void ADC_enable_watchdog_interrupt(ADC_TypeDef *p_adc);
void ADC_disable_watchdog_interrupt(ADC_TypeDef *p_adc);

uint16_t ADC_get_conversion_value(ADC_TypeDef *p_adc);

void ADC_set_alignment(ADC_TypeDef *p_adc, bool right_align);

void ADC_enable_scan_mode(ADC_TypeDef *p_adc);
void ADC_disable_scan_mode(ADC_TypeDef *p_adc);

void ADC_enable_continuous_mode(ADC_TypeDef *p_adc);
void ADC_disable_continuous_mode(ADC_TypeDef *p_adc);

void ADC_enable_discontinuous_mode(ADC_TypeDef *p_adc);
void ADC_disable_discontinuous_mode(ADC_TypeDef *p_adc);

void ADC_set_discontinuous_channel_count(ADC_TypeDef *p_adc, uint8_t count);

void ADC_select_channel(ADC_TypeDef *p_adc, uint8_t channel, uint8_t rank);

void ADC_set_sequence_length(ADC_TypeDef *p_adc, uint8_t length);

#endif // __ADC_H__