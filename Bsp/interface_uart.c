//
// Created by 10798 on 2023/1/4.
//
#include <stdio.h>
#include <string.h>
#include "interface_uart.h"

//--------------------------------------------------------------------------------
//DMA读出来的
uint8_t bluetooth_rx_buffer[WIFI_BUFFER_LENGTH];
uint8_t laser_rx_buffer[LASER_BUFFER_LENGTH];
uint8_t laser_tx_buffer[LASER_BUFFER_LENGTH];

void BlueToothReceived(uint8_t* _rx_buf)
{
    //已经验证可以接到了
    printf("%s",_rx_buf);

    //TODO:至少需要解析连接蓝牙与进入游戏

}

void BlueToothSend(const char* _str){
    HAL_UART_Transmit(&huart1,(uint8_t*)_str,strlen(_str),0xFFFF);
}

void BlueToothSendFire(int _bulletNum){
    char _str[20];
    sprintf(_str,"Fire|%d,", _bulletNum);
    BlueToothSend(_str);
}
void BlueToothSendHit(int _hp){
    char _str[20];
    sprintf(_str,"Hit|%d,", _hp);
    BlueToothSend(_str);
}
void BlueToothSendReload(int _bulletNum,int _magNum){
    char _str[20];
    sprintf(_str,"Reload|%d,%d,", _bulletNum, _magNum);
    BlueToothSend(_str);
}