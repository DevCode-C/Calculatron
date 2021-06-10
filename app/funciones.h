#include "string.h"
#include <stdio.h>

#ifndef FUNCIONES__H__
#define FUNCIONES__H__

HAL_StatusTypeDef checkComando(const uint8_t** check, uint8_t * comandoInput);
void DecToStr(uint8_t *buffer, int32_t val);
uint8_t number_digits(int32_t num);
#endif
