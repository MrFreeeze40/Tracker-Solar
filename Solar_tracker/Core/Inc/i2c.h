#ifndef __I2C_H__
#define __I2C_H__

#include "common.h"
#include "stm32f446xx.h"

#define PMOD_CLS_ADDR 0x48

/* --- Fonctions I2C Bas niveau --- */
err_t I2C1_Initialize(void);
err_t I2C1_WriteBytes(uint8_t deviceAddr, uint8_t* data, uint8_t length);

/* --- Fonctions Écran Pmod CLS --- */
err_t PMOD_CLS_Clear(void);
err_t PMOD_CLS_erase_line(uint8_t line);
err_t PMOD_CLS_Print(char* str);
err_t PMOD_CLS_SetCursor(uint8_t line, uint8_t col);
int PMOD_CLS_printf(const char *fmt, ...);

#endif // __I2C_H__
