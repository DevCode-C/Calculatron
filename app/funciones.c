#include "stm32f0xx.h"
#include <stdint.h>
#include "app_bsp.h"
#include "stm32f070xb.h"
#include "stm32f0xx_hal_gpio.h"
#include "stm32f0xx_hal_rcc.h"
#include "funciones.h"
#include <ctype.h>



void operationMat(uint8_t * buffer, int32_t A, int32_t B, uint8_t operation)
{
    uint8_t bufferTemp[30] = {0};
    uint8_t bufferTempD[20] = {0};
    switch (operation)
    {
    case 0:
        DecToStr(bufferTempD,A);
        strcpy((char*)bufferTemp,(const char*)bufferTempD);
        memset(bufferTempD,0,sizeof(bufferTempD));
        strcat((char*)bufferTemp, " + ");
        DecToStr(bufferTempD,B);
        strcat((char*)bufferTemp, (const char*)bufferTempD);
        memset(bufferTempD,0,sizeof(bufferTempD));
        strcat((char*)bufferTemp, " = ");
        DecToStr(bufferTempD,(A+B));
        strcat((char*)bufferTemp, (const char*)bufferTempD);
        memset(bufferTempD,0,sizeof(bufferTempD));
        strcat((char*)bufferTemp, " \r\n ");
        strcat((char*)bufferTemp, "\0");
        strcpy((char*)buffer,(const char*)bufferTemp);
        // sprintf((char*)buffer,"%ld + %ld = %ld\n",A,B,(A+B));
        break;

    case 1:
        DecToStr(bufferTempD,A);
        strcpy((char*)bufferTemp,(const char*)bufferTempD);
        memset(bufferTempD,0,sizeof(bufferTempD));
        strcat((char*)bufferTemp, " - ");
        DecToStr(bufferTempD,B);
        strcat((char*)bufferTemp, (const char*)bufferTempD);
        memset(bufferTempD,0,sizeof(bufferTempD));
        strcat((char*)bufferTemp, " = ");
        DecToStr(bufferTempD,(A-B));
        strcat((char*)bufferTemp, (const char*)bufferTempD);
        memset(bufferTempD,0,sizeof(bufferTempD));
        strcat((char*)bufferTemp, " \r\n ");
        strcat((char*)bufferTemp, "\0");
        strcpy((char*)buffer,(const char*)bufferTemp);
        // sprintf((char*)buffer,"%ld - %ld = %ld\n",A,B,(A-B));
        break;

    case 2:
        DecToStr(bufferTempD,A);
        strcpy((char*)bufferTemp,(const char*)bufferTempD);
        memset(bufferTempD,0,sizeof(bufferTempD));
        strcat((char*)bufferTemp, " * ");
        DecToStr(bufferTempD,B);
        strcat((char*)bufferTemp, (const char*)bufferTempD);
        memset(bufferTempD,0,sizeof(bufferTempD));
        strcat((char*)bufferTemp, " = ");
        DecToStr(bufferTempD,(A*B));
        strcat((char*)bufferTemp, (const char*)bufferTempD);
        memset(bufferTempD,0,sizeof(bufferTempD));
        strcat((char*)bufferTemp, " \r\n ");
        strcat((char*)bufferTemp, "\0");
        strcpy((char*)buffer,(const char*)bufferTemp);
        // sprintf((char*)buffer,"%ld * %ld = %ld\n",A,B,(A*B));
        break;

    case 3:
        DecToStr(bufferTempD,A);
        strcpy((char*)bufferTemp,(const char*)bufferTempD);
        memset(bufferTempD,0,sizeof(bufferTempD));
        strcat((char*)bufferTemp, " / ");
        DecToStr(bufferTempD,B);
        strcat((char*)bufferTemp, (const char*)bufferTempD);
        memset(bufferTempD,0,sizeof(bufferTempD));
        strcat((char*)bufferTemp, " = ");
        DecToStr(bufferTempD,(A/B));
        strcat((char*)bufferTemp, (const char*)bufferTempD);
        memset(bufferTempD,0,sizeof(bufferTempD));
        strcat((char*)bufferTemp, " \r\n ");
        strcat((char*)bufferTemp, "\0");
        strcpy((char*)buffer,(const char*)bufferTemp);
        // sprintf((char*)buffer,"%ld / %ld = %ld\n",A,B,(A/B));
        break;
    }
}


HAL_StatusTypeDef checkComando(const uint8_t** check, uint8_t * comandoInput, uint8_t * operacion)
{
    HAL_StatusTypeDef flagTemp = HAL_BUSY;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (strcmp((const char *)check[i],(const char*)comandoInput) == 0)
        {
            flagTemp = HAL_OK;
            *operacion = i;
            break;
        }
        else
        {
            flagTemp = HAL_ERROR;
        }
    }

    return flagTemp;
}

HAL_StatusTypeDef checkCharDigit(uint8_t * charDigit)
{
    // uint8_t Charnumber = strlen((const char*)charDigit);
    HAL_StatusTypeDef flagNumber = HAL_BUSY;
    uint8_t i = 0;
    if (charDigit[0] == '-')
    {
        i++;
    }
    
    // for (; charDigit[i] != '\0'; i++)
    // for (; i < Charnumber; i++)
    // {
    //     // if ((*charDigit >= '0' && *charDigit <= '9') || ((*charDigit == '-') || ((*charDigit == '\r'))))
    //     if ((isdigit(charDigit[i])))
    //     {
    //         flagNumber = HAL_OK;
    //     }
    //     else
    //     {
    //         flagNumber = HAL_ERROR;
    //         break;
    //     }
    //     // charDigit[i];
    // }
    while ( charDigit[i] != '\0')
    {
        if ((charDigit[i] >= '0' && charDigit[i] <= '9') )
        {
            flagNumber = HAL_OK;
            i++;
        }
        else if (charDigit[i] == '\r')
        {
            charDigit[i] = '\0';
            flagNumber = HAL_OK;
            break;
        }
        else
        {
            flagNumber = HAL_ERROR;
            break;
        }
        
    }
    
    return flagNumber;
    
}

int32_t CharToDigit(uint8_t* charDigit)
{
    // uint8_t Charnumber = strlen((const char*)charDigit);
    // int32_t digTemp = 0;
    // for (uint8_t i = 0; i < Charnumber; i++)
    // {
    //     if (charDigit[0] == '-')
    //     {
    //         i++;
    //     }
    //     digTemp = digTemp*10 + (*charDigit - '0');
    //     charDigit++;
    // }
    // if (charDigit[0] == '-')
    // {
    //     return (digTemp*(-1));
    // }
    // else
    // {
    //     return digTemp;
    // }
        // Initialize result

    int res = 0;
    int sign = 1;

    int i = 0;
    if (charDigit[0] == '-') {

        sign = -1;
        i++;

    }
    for (; charDigit[i] != '\0'; ++i)

        res = res * 10 + charDigit[i] - '0';

    return sign * res;
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
