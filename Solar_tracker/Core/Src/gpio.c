#include "gpio.h"
#include "common.h"
#include "stm32f446xx.h"

err_t GPIO_SetPinMode(GPIO_TypeDef *pGPIO, uint8_t pin, enum GPIO_PinMode mode) {
    if (pin > 15) return ERR_INVALID_PARAM;

    uint8_t offset = pin << 1;
    pGPIO->MODER &= ~(0b11 << offset); // reset the two bits
    pGPIO->MODER |= (mode << offset);

    return ERR_NONE;
}

err_t GPIO_SetOutputType(GPIO_TypeDef *pGPIO, uint8_t pin, enum GPIO_OutputType type) {
    if (pin > 15) return ERR_INVALID_PARAM;

    GPIOA->OTYPER &= ~(0b1 << pin); 
    GPIOA->OTYPER |= (type << pin);

    return ERR_NONE;
}

err_t initialize_GPIO() {
    if (GPIO_SetPinMode(GPIOA, 5, GPIO_OUTPUT_MODE)) {
        return ERR_UNDEFINED;
    }

    if (GPIO_SetOutputType(GPIOA, 5, GPIO_PUSH_PULL_OUTPUT_TYPE)) {
        return ERR_UNDEFINED;
    }

    if (GPIO_SetPinMode(GPIOB, 3, GPIO_ALTERNATE_FUNCTION_MODE)) {
        return ERR_UNDEFINED;
    }

    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL3);
    GPIOB->AFR[0] |= (1 << GPIO_AFRL_AFSEL3_Pos);

    if (GPIO_SetPinMode(GPIOC, 13, GPIO_INPUT_MODE)) {
        return ERR_UNDEFINED;
    }

    return ERR_NONE;
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
