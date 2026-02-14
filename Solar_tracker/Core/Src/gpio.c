#include "gpio.h"
#include "stm32f446xx.h"

err_t GPIO_SetPinMode(GPIO_TypeDef *pGPIO, uint8_t pin, enum GPIO_PinMode mode) {
    if (pin > 15) return INVALID_PARAMETER;

    uint8_t offset = pin << 1;
    pGPIO->MODER &= ~(0b11 << offset); // reset the two bits
    pGPIO->MODER |= (mode << offset);

    return NO_ERROR;
}

err_t GPIO_SetOutputType(GPIO_TypeDef *pGPIO, uint8_t pin, enum GPIO_OutputType type) {
    if (pin > 15) return INVALID_PARAMETER;

    GPIOA->OTYPER &= ~(0b1 << pin); 
    GPIOA->OTYPER |= (type << pin);

    return NO_ERROR;
}

err_t initialize_GPIO() {
    if (GPIO_SetPinMode(GPIOA, 5, GPIO_OUTPUT_MODE)) {
        return UNDEFINED_ERROR;
    }

    if (GPIO_SetOutputType(GPIOA, 5, GPIO_PUSH_PULL_OUTPUT_TYPE)) {
        return UNDEFINED_ERROR;
    }

    return NO_ERROR;
}

void GPIO_OutputSetPin(GPIO_TypeDef *pGPIO, uint8_t pin) {
    pGPIO->ODR |= (1 << pin);
}

void GPIO_OutputResetPin(GPIO_TypeDef *pGPIO, uint8_t pin) {
    pGPIO->ODR &= ~(1 << pin);
}

void GPIO_OutputTogglePin(GPIO_TypeDef *pGPIO, uint8_t pin) {
    pGPIO->ODR ^= (1 << pin);
}

void GPIO_OutputAssignPin(GPIO_TypeDef *pGPIO, uint8_t pin, uint8_t value) {
    if(value) {
        GPIO_OutputSetPin(pGPIO, pin);
    } else {
        GPIO_OutputResetPin(pGPIO, pin);
    }
}
