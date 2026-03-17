#include "i2c.h"
#include "gpio.h"

err_t I2C1_Initialize(void) {
    // 1. Activation des horloges (I2C1 et GPIOB pour PB8/PB9)
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // 2. Configuration des GPIOs via ton driver gpio.c
    GPIO_SetPinMode(GPIOB, 8, GPIO_ALTERNATE_FUNCTION_MODE); // SCL
    GPIO_SetPinMode(GPIOB, 9, GPIO_ALTERNATE_FUNCTION_MODE); // SDA
    
    // Type Open-Drain indispensable pour l'I2C
    GPIOB->OTYPER |= (GPIO_OPEN_DRAIN_OUTPUT_TYPE << 8) | (GPIO_OPEN_DRAIN_OUTPUT_TYPE << 9);
    
    // Sélection de l'Alternate Function AF4 (I2C) dans les registres AFR
    GPIOB->AFR[1] &= ~((0xF << 0) | (0xF << 4));
    GPIOB->AFR[1] |= (4 << 0) | (4 << 4);

    // 3. Configuration de l'I2C (APB1 est à 42MHz pour un système à 84MHz)
    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    I2C1->CR2 = 42;      // Fréquence d'entrée APB1 = 42 MHz
    I2C1->CCR = 210;     // Mode Standard 100kHz (42MHz / (2 * 100kHz))
    I2C1->TRISE = 43;    // Temps de montée max
    
    I2C1->CR1 |= I2C_CR1_PE; // Activation périphérique
    
    return ERR_NONE;
}

err_t I2C1_WriteByte(uint8_t deviceAddr, uint8_t data) {
    // Attente bus libre
    while (I2C1->SR2 & I2C_SR2_BUSY);

    // Condition START
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));

    // Envoi Adresse esclave + bit d'écriture (0)
    I2C1->DR = (deviceAddr << 1);
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2; // Lecture SR2 pour acquitter l'adresse

    // Envoi de la donnée
    I2C1->DR = data;
    while (!(I2C1->SR1 & I2C_SR1_TXE));

    // Condition STOP
    I2C1->CR1 |= I2C_CR1_STOP;

    return ERR_NONE;
}

/* --- Implémentation Écran --- */

err_t PMOD_CLS_Clear(void) {
    I2C1_WriteByte(PMOD_CLS_ADDR, 0x1B); // ESC
    I2C1_WriteByte(PMOD_CLS_ADDR, '[');
    I2C1_WriteByte(PMOD_CLS_ADDR, 'j');  // Commande effacer
    for(volatile int i=0; i<10000; i++); // Délai : l'écran est lent à effacer
    return ERR_NONE;
}

err_t PMOD_CLS_Print(char* str) {
    while(*str) {
        I2C1_WriteByte(PMOD_CLS_ADDR, (uint8_t)*str++);
        for(volatile int i=0; i<2000; i++); // Petit délai entre chaque caractère
    }
    return ERR_NONE;
}

err_t PMOD_CLS_SetCursor(uint8_t line, uint8_t col) {
    I2C1_WriteByte(PMOD_CLS_ADDR, 0x1B);
    I2C1_WriteByte(PMOD_CLS_ADDR, '[');
    I2C1_WriteByte(PMOD_CLS_ADDR, line + '0');
    I2C1_WriteByte(PMOD_CLS_ADDR, ';');
    I2C1_WriteByte(PMOD_CLS_ADDR, col + '0');
    I2C1_WriteByte(PMOD_CLS_ADDR, 'H');
    return ERR_NONE;
}
