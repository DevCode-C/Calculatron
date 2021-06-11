#include "string.h"
#include <stdio.h>

#ifndef FUNCIONES__H__
#define FUNCIONES__H__

void operationMat(uint8_t * buffer, int32_t A, int32_t B, uint8_t operation);

HAL_StatusTypeDef checkComando(const uint8_t** check, uint8_t * comandoInput, uint8_t * operacion);

HAL_StatusTypeDef checkCharDigit(uint8_t * charDigit);

int32_t CharToDigit(uint8_t* charDigit);

void DecToStr(uint8_t *buffer, int32_t val);

uint8_t number_digits(int32_t num);
#endif
