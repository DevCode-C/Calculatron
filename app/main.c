#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "app_bsp.h"
#include "stm32f070xb.h"
#include "stm32f0xx_hal_conf.h"
#include "string.h"
#include "stm32f0xx_hal.h"
#include "funciones.h"
#include "ctype.h"

/**------------------------------------------------------------------------------------------------
Brief.- Punto de entrada del programa
-------------------------------------------------------------------------------------------------*/

#define strlen_p(x) strlen((const char*)x)
#define SPACE       32  //  "space -> ' ' "
#define PER         42  //  " * "
#define ADD         43  //  " + "
#define MINUS       45  //  " - "
#define DIV         47  //  " / "


const uint8_t* msgError   =    (uint8_t*)"ERROR\n";
const uint8_t* msgOk   =    (uint8_t*)"OK\n";

const uint8_t* comando[4] =    {(uint8_t*)"SUM",
                                (uint8_t*)"SUB",
                                (uint8_t*)"MUL",
                                (uint8_t*)"DIV",
                                                };

UART_HandleTypeDef UartHandle;
__IO ITStatus uartState = SET;
__IO ITStatus status = RESET;
__IO HAL_StatusTypeDef flag = HAL_OK;


uint8_t RxByte;
uint8_t RxBuffer[30] = {0};
uint8_t RxBufferTemp[30] = {0};
uint8_t dec[10] = {0};
uint32_t tickTimer; 

void UART_Init(void);


int main( void )
{
    HAL_Init( );
    UART_Init();

    char *temp = NULL;
    tickTimer = HAL_GetTick();
    for (; ;)
    {

        if (status == SET )
        {
            strcpy((char*)RxBufferTemp,(const char*)RxBuffer);
            status = RESET;
            temp = strtok((char*)RxBufferTemp," "); 
            
            if (temp != NULL)
            {
                // for (uint8_t i = 0; i < 4; i++)
                // {
                //     if (strcmp((const char *)comando[i],temp) == 0)
                //     {
                //         flag = HAL_OK;
                //         break;
                //     }
                //     else
                //     {
                //         flag = HAL_ERROR;
                //     }
                // }
                // if (/*uartState &&*/ flag == HAL_OK)
                // {
                //     // uartState = RESET;
                //     // sprintf(dec,"%d",number_digits(-2));
                //     // DecToStr(dec,13);
                //     // HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)dec,strlen_p(dec));
                //     temp = strtok(NULL," ");
                //     if (temp != NULL)
                //     {
                //         do
                //         {
                //             if (*temp >= '0' && *temp <= '9')
                //             {
                //                 flag = HAL_OK;
                //             }
                //             else
                //             {
                //                 flag = HAL_ERROR;
                //                 break;
                //             }
                            
                //             temp++;
                            
                //         } while (*temp == '\0');
                        
                //         // HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)temp,strlen_p(temp));
                //     }
                    
                // }
                // else if (uartState && flag == HAL_ERROR)
                // {
                //     uartState = RESET;
                //     HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)msgError,strlen_p(msgError));
                //     temp = NULL;
                // }

                if (checkComando(comando,(uint8_t*)temp) == HAL_OK)
                {
                    HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)msgOk,strlen_p(msgOk));
                }
                else 
                {
                    HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)msgError,strlen_p(msgError));
                }                
                
            }
        }

        if (HAL_GetTick() - tickTimer > 100)
        {
            tickTimer = HAL_GetTick();
            HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
        }
        
        
    } 
    return 0u;
}


void UART_Init()
{
    UartHandle.Instance             = USART2;
    UartHandle.Init.BaudRate        = 115200;
    UartHandle.Init.WordLength      = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits        = UART_STOPBITS_1;
    UartHandle.Init.Parity          = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl       = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode            = UART_MODE_TX_RX;
    UartHandle.Init.OverSampling    = UART_OVERSAMPLING_16;

    HAL_UART_Init(&UartHandle);
    HAL_UART_Receive_IT(&UartHandle,&RxByte,1);
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    uartState = SET;
    memset(RxBuffer,0,sizeof(RxBuffer));
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    static uint32_t i = 0;
    RxBuffer[i] = RxByte;
    i++;
    if(RxBuffer[i-1] == '\r')
    {
        status = SET;
        i=0;
    }
    HAL_UART_Receive_IT(&UartHandle,&RxByte,1);
}