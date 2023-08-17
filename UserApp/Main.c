//
// Created by 10798 on 2022/10/5.
//
#include <stdbool.h>
#include <tim.h>
#include <interface_uart.h>
#include <pwm.h>
#include <retarget.h>
#include <utils/ctrl_math.h>
#include <wave.h>
#include "common_inc.h"

/* Thread Definitions -----------------------------------------------------*/

/* Timer Callbacks -------------------------------------------------------*/


/* UART Callbacks -------------------------------------------------------*/
//空闲中断在这里进行处理
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(huart->Instance==USART1)
    {
        //重新打开DMA接收 idle中断
        HAL_UARTEx_ReceiveToIdle_DMA(&BLUETOOTH_UART, wifi_rx_buffer, sizeof(wifi_rx_buffer));

    }
}

/* Default Entry -------------------------------------------------------*/
void Main(void) {
//    RetargetInit(&WIFI_UART);

    //wifi 串口DMA空闲中断 enable
    HAL_UARTEx_ReceiveToIdle_DMA(&BLUETOOTH_UART, wifi_rx_buffer, sizeof(wifi_rx_buffer));

    while (true){
        //SPEAKER PWM DMA Send, not necessary to enable
        HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2,(uint32_t*)SOUND_DATA, SOUND_LENGTH);

//        printf("Hello World!\r\n");
        //Blink
        HAL_GPIO_TogglePin(RGB_G_GPIO_Port,RGB_G_Pin);
        //-----------------------------Delay
        HAL_Delay(5000);
    }
}
