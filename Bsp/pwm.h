//
// Created by 10798 on 2023/1/6.
//

#ifndef ATK_F405_FW_PWM_H
#define ATK_F405_FW_PWM_H

#include <stdint-gcc.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LASER_PWM 5



void PWMInit(void);

void PWMCmdSend(void);


#ifdef __cplusplus
}
#endif


#endif //ATK_F405_FW_PWM_H
