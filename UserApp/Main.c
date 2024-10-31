//
// Created by 10798 on 2022/10/5.
//
#include <stdbool.h>
#include <tim.h>
#include <pwm.h>
#include <multi_button.h>
#include <menu.h>
#include <MultiTimer.h>
#include "common_inc.h"
#include "player.h"
#include "usbd_cdc_if.h"
#include "interface_use.h"


/* Thread Definitions -----------------------------------------------------*/

/* Timer Callbacks -------------------------------------------------------*/
//multi定时器相关
uint64_t PlatformTicksGetFunc(void)
{
    return (uint64_t)HAL_GetTick();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

    if (htim->Instance == TIM4) {
        //5ms
        //按键扫描
        button_ticks();

        //USB 接收判断
        USBReceived(usb_rx_buffer);

        //时间更新
        PlayerTimeUpdate(&player);
    }
}

///* UART Callbacks -------------------------------------------------------*/
////空闲中断在这里进行处理
//void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
//{
//    if(huart->Instance==USART1)
//    {
////        HAL_GPIO_TogglePin(BOARD_LED_GPIO_Port,BOARD_LED_Pin);
//
////        BlueToothReceived(bluetooth_rx_buffer);
//
//        //重新打开DMA接收 idle中断
//        HAL_UARTEx_ReceiveToIdle_DMA(&BLUETOOTH_UART, bluetooth_rx_buffer, sizeof(bluetooth_rx_buffer));
//
//    }
//}

uint8_t char1[]={0x5A};

/* Default Entry -------------------------------------------------------*/
void Main(void) {

    ////==========================BT相关===========================================
    //BT 串口DMA空闲中断 enable
//    HAL_UARTEx_ReceiveToIdle_DMA(&BLUETOOTH_UART, bluetooth_rx_buffer, sizeof(bluetooth_rx_buffer));

    // 蓝牙初始化配置
    //TODO:注意这里每个新机器都要重新设置一次，设置完了之后就会一直保持是30ms了。
//    BlueToothSend("AT+ADVI=30\r\n");

    ////==========================软件定时器相关======================================
    MultiTimerInstall(PlatformTicksGetFunc);

    ////==========================按键相关===========================================
    // 初始化按键（硬件相关）
    button_init(&buttonFire, read_button_GPIO, 1,buttonFireId);
    button_init(&buttonReload, read_button_GPIO, 0,buttonReloadId);
    button_init(&buttonLaser, read_button_GPIO, 0,buttonLaserId);
    // 按键回调函数（软件相关）
    // fire按钮
    button_attach(&buttonFire, PRESS_DOWN,     BTN_SINGLE_Click_Handler);
    button_attach(&buttonFire, LONG_PRESS_HOLD,     BTN_LONG_Press_Hold_Handler);
    // reload按钮
    button_attach(&buttonReload, LONG_PRESS_START,     BTN_LONG_Press_Start_Handler);
    // laser按钮
    button_attach(&buttonLaser, PRESS_DOWN,     BTN_SINGLE_Click_Handler);
    //打开btn
    button_start(&buttonFire);
    button_start(&buttonReload);
    button_start(&buttonLaser);

    ////==========================LASER相关===========================================
    PWMInit();
    PWMCmdSend();
    HAL_GPIO_WritePin(LASER_TX_GPIO_Port,LASER_TX_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(RX_LED_GPIO_Port,RX_LED_Pin,GPIO_PIN_RESET);

    ////==========================游戏逻辑相关===========================================
    PlayerInit(&player);

//    PlayerEnterBattle(&player);

    //启动定时器
    HAL_TIM_Base_Start_IT(&htim4);

    while (true){
        //定时器后台处理
        MultiTimerYield();
        //-----------------------------Delay
        HAL_Delay(1);


    }
}
