//
// Created by 10798 on 2023/1/4.
//

#ifndef ATK_F405_FW_IBUS_H
#define ATK_F405_FW_IBUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usart.h"

#define WIFI_BUFFER_LENGTH     18
extern uint8_t bluetooth_rx_buffer[WIFI_BUFFER_LENGTH];

#define LASER_BUFFER_LENGTH     2
extern uint8_t laser_rx_buffer[LASER_BUFFER_LENGTH];
extern uint8_t laser_tx_buffer[LASER_BUFFER_LENGTH];

void BlueToothReceived(uint8_t* _rx_buffer);

void BlueToothSendFire(int _bulletNum);
void BlueToothSendHit(int _hp);
void BlueToothSendReload(int _bulletNum,int _magNum);
void BlueToothSend(const char* _str);

#ifdef __cplusplus
}
#endif

#endif //ATK_F405_FW_IBUS_H
