//
// Created by 10798 on 2023/8/22.
//

#ifndef TERMINAL_MENU_H
#define TERMINAL_MENU_H

#include <stdio.h>
#include "MultiTimer.h"

enum ButtonIds{
    buttonFireId,
    buttonReloadId,
    buttonLaserId
};

extern struct Button buttonFire;
extern struct Button buttonReload;
extern struct Button buttonLaser;

extern MultiTimer timer1;
extern MultiTimer timer2;
extern MultiTimer timer3;

void Timer1MAGCallback(MultiTimer* timer, void* userData);
void Timer2FireCallback(MultiTimer* timer, void* userData);
void Fire(void);

void BTN_SINGLE_Click_Handler(void* btn);
void BTN_LONG_Press_Hold_Handler(void* btn);
void BTN_LONG_Press_Start_Handler(void* btn);
uint8_t read_button_GPIO(uint8_t button_id);

#endif //TERMINAL_MENU_H
