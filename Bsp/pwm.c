//
// Created by 10798 on 2023/1/6.
//

#include "pwm.h"
#include "tim.h"

// LASER PWM
// 分频系数 35 9
//占空比： 0~9 方波给5即可

// SPEAKER PWM
// 分频系数 16 255
// 最终频率： 72M / (16+1) / (255+1) = 16.544kHz ~= 16kHz
// 占空比： 0~255 占空比通过DMA送，不用管


void PWMInit(void){
    //LASER PWM使能
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}


void PWMCmdSend(void){
    //LASER 发送
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, LASER_PWM);

}

