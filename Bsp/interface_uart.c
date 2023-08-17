//
// Created by 10798 on 2023/1/4.
//

#include <string.h>
#include "interface_uart.h"

//--------------------------------------------------------------------------------
//DMA读出来的
uint8_t wifi_rx_buffer[WIFI_BUFFER_LENGTH];

void WIFIReceived(uint8_t* _rx_buf)
{
//    memcpy(&shiftGears, &_rx_buf[0], sizeof(uint8_t));
//    memcpy(&handbrake, &_rx_buf[1], sizeof(uint8_t));
//    memcpy(&steeringWheel, &_rx_buf[2], sizeof(float));
//    memcpy(&throttle, &_rx_buf[6], sizeof(float));
//    memcpy(&brake, &_rx_buf[10], sizeof(float));
//    memcpy(&clutch, &_rx_buf[14], sizeof(float));
}