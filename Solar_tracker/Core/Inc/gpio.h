#ifndef __GPIO_H__
#define __GPIO_H__
#include "common.h"
#include "stm32f446xx.h"

enum GPIO_PinMode {
    GPIO_INPUT_MODE = 0b00,
    GPIO_OUTPUT_MODE = 0b01,
    GPIO_ALTERNATE_FUNCTION_MODE = 0b10,
    GPIO_ANALOG_MODE = 0b11
};

enum GPIO_OutputType {
    GPIO_PUSH_PULL_OUTPUT_TYPE = 0b0,
    GPIO_OPEN_DRAIN_OUTPUT_TYPE = 0b1,
};

err_t GPIO_SetPinMode(GPIO_TypeDef *pGPIO, uint8_t pin, enum GPIO_PinMode mode);

err_t GPIO_SetOutputType(GPIO_TypeDef *pGPIO, uint8_t pin, enum GPIO_OutputType type);

err_t initialize_GPIO();

void GPIO_OutputSetPin(GPIO_TypeDef *pGPIO, uint8_t pin);
void GPIO_OutputResetPin(GPIO_TypeDef *pGPIO, uint8_t pin);
void GPIO_OutputTogglePin(GPIO_TypeDef *pGPIO, uint8_t pin);
void GPIO_OutputAssignPin(GPIO_TypeDef *pGPIO, uint8_t pin, uint8_t value);

#endif // __GPIO_H__