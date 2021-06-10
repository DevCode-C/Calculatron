#include "stm32f0xx.h"
#include <stdint.h>
#include "app_bsp.h"
#include "stm32f070xb.h"
#include "stm32f0xx_hal_gpio.h"
#include "stm32f0xx_hal_rcc.h"
#include "funciones.h"

HAL_StatusTypeDef checkComando(const uint8_t** check, uint8_t * comandoInput)
{
    HAL_StatusTypeDef flagTemp = HAL_BUSY;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (strcmp((const char *)check[i],(const char*)comandoInput) == 0)
        {
            flagTemp = HAL_OK;
            break;
        }
        else
        {
            flagTemp = HAL_ERROR;
        }
    }

    return flagTemp;
}


void DecToStr(uint8_t *buffer, int32_t val)
{
    uint8_t nElements = number_digits(val)+1;
    uint8_t bufferTemp[nElements];
    uint8_t i;
    if (val < 0)
    {   val *= (-1);
        for (i = 1; i <= nElements; i++)
        {
            bufferTemp[nElements - i] =(uint8_t) ((val % 10UL) + '0');
            val/=10;
        }
        bufferTemp[i - 1] = '\0';
        bufferTemp[0] = '-';
        strcpy((char *)buffer,(const char*)bufferTemp);
    }
    else
    {
        for (i = 1; i <= nElements; i++)
        {
            bufferTemp[nElements - i] =(uint8_t) ((val % 10UL) + '0');
            val/=10;
        }
        bufferTemp[i - 1] = '\0';
        strcpy((char *)buffer,(const char*)&bufferTemp[1]);
    }

    
}

uint8_t number_digits(int32_t num)
{
    uint8_t count = 0;

    if (num < 0)
    {
        num *= (-1);
    }
    
    while(num > 0)
    {
        count++;
        num /= 10;
    }

    return count;
}
