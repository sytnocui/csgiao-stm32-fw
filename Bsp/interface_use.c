//
// Created by sytnocui on 2024/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "interface_use.h"
#include "usbd_cdc_if.h"
#include "player.h"

bool usb_rx_flag = false;
uint32_t usb_rx_len=0;
uint8_t usb_rx_buffer[USB_BUFFER_LENGTH]={0};

void USBReceived(uint8_t* _rx_buf)
{
    //标志位判断
    if (usb_rx_flag == false){
        return;
    }
    usb_rx_flag = false;

    HAL_GPIO_TogglePin(BOARD_LED_GPIO_Port,BOARD_LED_Pin);

    USBSend((char*) _rx_buf);

    //进入战斗
    if (strcmp((char *)_rx_buf, "EnterBattle") == 0){
        PlayerEnterBattle(&player);
    }
    else if (strcmp((char *)_rx_buf, "QuitBattle") == 0){
        PlayerQuitBattle(&player);
    }
    else if (strcmp((char *)_rx_buf, "Resurrect") == 0){
        PlayerResurrect(&player);
    }

    memset(usb_rx_buffer, 0, USB_BUFFER_LENGTH);

}


//重要！！！总长度必须小于64byte，否则会被强制分包
void USBSend(const char* _str){
    CDC_Transmit_FS((uint8_t*) _str,strlen(_str));
}

void USBSendFire(int _bulletNum){
    char _str[20];
    sprintf(_str,"Fire|%d,", _bulletNum);
    USBSend(_str);
}

void USBSendHit(int _hp){
    char _str[20];
    sprintf(_str,"Hit|%d,", _hp);
    USBSend(_str);
}

void USBSendReload(int _bulletNum,int _magNum){
    char _str[20];
    sprintf(_str,"Reload|%d,%d,", _bulletNum, _magNum);
    USBSend(_str);
}