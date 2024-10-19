//
// Created by 10798 on 2023/8/22.
//

#include <main.h>
#include "menu.h"
#include "multi_button.h"
#include "player.h"

////==========================按键相关=========================================
struct Button buttonFire;
struct Button buttonReload;
struct Button buttonLaser;

////==========================软件定时器相关=========================================
MultiTimer timer1;
MultiTimer timer2;
MultiTimer timer3;
////==============================================================================

void Timer1MAGCallback(MultiTimer* timer, void* userData)
{
    HAL_GPIO_WritePin(MAG_GPIO_Port,MAG_Pin,GPIO_PIN_RESET);
}

void Timer2FireCallback(MultiTimer* timer, void* userData)
{
    HAL_GPIO_WritePin(LASER_TX_GPIO_Port,LASER_TX_Pin,GPIO_PIN_SET);
}

void Timer3HitCallback(MultiTimer* timer, void* userData)
{
    HAL_GPIO_WritePin(RX_LED_GPIO_Port,RX_LED_Pin,GPIO_PIN_RESET);
}

void Fire(void){
    HAL_GPIO_WritePin(LASER_TX_GPIO_Port,LASER_TX_Pin,GPIO_PIN_RESET); //发射
    MultiTimerStart(&timer2, 100, Timer2FireCallback, NULL);

    HAL_GPIO_WritePin(MAG_GPIO_Port,MAG_Pin,GPIO_PIN_SET); //力反馈
    MultiTimerStart(&timer1, 50, Timer1MAGCallback, NULL);
}
void Hit(void){
    HAL_GPIO_WritePin(RX_LED_GPIO_Port,RX_LED_Pin,GPIO_PIN_SET);
    MultiTimerStart(&timer3, 500, Timer3HitCallback, NULL);
}

////==========================按键驱动相关===========================================
//单击按键
void BTN_SINGLE_Click_Handler(void* btn)
{
    Button *temp_button = (Button *)btn;
    switch(temp_button->button_id)
    {
        case buttonFireId: //开火
            PlayerFireUpdate(&player);


            break;
        case buttonLaserId: //受伤
            PlayerHitUpdate(&player);
//            HAL_GPIO_TogglePin(RX_LED_GPIO_Port,RX_LED_Pin);
//            HAL_GPIO_WritePin(RX_LED_GPIO_Port,RX_LED_Pin,GPIO_PIN_SET);
Hit();
            break;
        default:
            break;
    }
}

//开始长按，只有换弹用这个
void BTN_LONG_Press_Start_Handler(void* btn)
{
    Button *temp_button = (Button *)btn;
    switch(temp_button->button_id)
    {
        case buttonFireId:
            PlayerFireUpdate(&player);
            //TODO:连发之后统一处理，与射速有关先不管。
            break;
        case buttonReloadId:
            PlayerReloadUpdate(&player);
//            HAL_GPIO_TogglePin(BOARD_LED_GPIO_Port,BOARD_LED_Pin);

            break;
        default:
            break;
    }
}

// 保持长按，只有连发是这种
void BTN_LONG_Press_Hold_Handler(void* btn)
{
    Button *temp_button = (Button *)btn;
    switch(temp_button->button_id)
    {
        case buttonFireId:
            PlayerFireUpdate(&player);
//            HAL_GPIO_TogglePin(BOARD_LED_GPIO_Port,BOARD_LED_Pin);

            //TODO:连发之后统一处理，与射速有关先不管。
            break;
        default:
            break;
    }
}



//按键函数定义
uint8_t read_button_GPIO(uint8_t button_id)
{
    switch(button_id)
    {
        case buttonFireId:
            return HAL_GPIO_ReadPin(KEY_FIRE_GPIO_Port, KEY_FIRE_Pin);
        case buttonReloadId:
            return HAL_GPIO_ReadPin(KEY_RELOAD_GPIO_Port, KEY_RELOAD_Pin);
        case buttonLaserId:
            return HAL_GPIO_ReadPin(LASER_RX_GPIO_Port, LASER_RX_Pin);
        default:
            return 0;
    }
}
