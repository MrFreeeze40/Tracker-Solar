#include "i2c.h"
#include "gpio.h"
#include <stdarg.h>
#include <stdio.h>

// Fonction de délai simple
void delay_ms(uint32_t ms) {
    for(volatile uint32_t i = 0; i < ms * 1000; i++); // Approximation pour 84MHz
}

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

err_t I2C1_WriteBytes(uint8_t deviceAddr, uint8_t* data, uint8_t length) {
    if (length == 0) return ERR_NONE;

    // Attente bus libre
    while (I2C1->SR2 & I2C_SR2_BUSY);

    // Condition START
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));

    // Envoi Adresse esclave + bit d'écriture (0)
    I2C1->DR = (deviceAddr << 1);
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2; // Lecture SR2 pour acquitter l'adresse

    for (uint8_t i = 0; i < length; i++) {
        // Envoi de la donnée
        I2C1->DR = data[i];
        while (!(I2C1->SR1 & I2C_SR1_TXE));
    }

    // Condition STOP
    I2C1->CR1 |= I2C_CR1_STOP;

    return ERR_NONE;
}

/* --- Implémentation Écran --- */

err_t PMOD_CLS_Clear(void) {
    uint8_t cmd[] = {0x1B, 0X5B, 'j'};
    I2C1_WriteBytes(PMOD_CLS_ADDR, cmd, 3);
    delay_ms(2); // Délai pour l'effacement
    return ERR_NONE;
}

err_t PMOD_CLS_Print(char* str) {
    while(*str) {
        I2C1_WriteByte(PMOD_CLS_ADDR, (uint8_t)*str++);
        delay_ms(1); // Délai entre caractères
    }
    return ERR_NONE;
}

err_t PMOD_CLS_erase_line(uint8_t line) {
    if (line > 1) return ERR_INVALID_PARAM;
    PMOD_CLS_SetCursor(line, 0);
    uint8_t cmd[] = {0x1B, 0X5B, '0', 'K'};
    I2C1_WriteBytes(PMOD_CLS_ADDR, cmd, 4);
    delay_ms(2); // Délai pour l'effacement
    return ERR_NONE;
}

err_t PMOD_CLS_SetCursor(uint8_t line, uint8_t col) {
    uint8_t transmitted_char = 6;
    if (line > 1) return ERR_INVALID_PARAM;
    if (col > 15) return ERR_INVALID_PARAM;
    char line_char = '0' + line;
    char col_chars[2];
    uint8_t cmd[] = {0x1B, 0X5B, line_char, ';', col_chars[1], col_chars[0], 'H'};
    if (col > 9) {
        transmitted_char++;
        cmd[4] = '1';
        cmd[5] = '0' + col % 10;
        cmd[6] = 'H';
    } else {
        cmd[4] = '0' + col % 10;
        cmd[5] = 'H';
    }

    I2C1_WriteBytes(PMOD_CLS_ADDR, cmd, transmitted_char);
    delay_ms(1); // Délai pour le positionnement
    return ERR_NONE;
}


int PMOD_CLS_printf(const char *fmt, ...) {
    char buf[16];
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    if (len < 0) return -1;
    if (len > (int)sizeof(buf)-1) len = sizeof(buf)-1;

    // Envoi en I2C en un seul bloc si disponible
    // -> si PMOD_CLS_Print existant envoie char par char, c'est OK aussi
    for (int i = 0; i < len; i++) {
        I2C1_WriteByte(PMOD_CLS_ADDR, (uint8_t)buf[i]);
    }
    return len;
}
