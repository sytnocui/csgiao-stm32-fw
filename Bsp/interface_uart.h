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
extern uint8_t wifi_rx_buffer[WIFI_BUFFER_LENGTH];

void WIFIReceived(uint8_t* _rx_buffer);


#ifdef __cplusplus
}
#endif

#endif //ATK_F405_FW_IBUS_H
