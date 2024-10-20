//
// Created by sytnocui on 2024/10/20.
//

#ifndef ARPUBG_FW_V2_INTERFACE_USE_H
#define ARPUBG_FW_V2_INTERFACE_USE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define USB_BUFFER_LENGTH     255

extern bool usb_rx_flag;
extern uint32_t usb_rx_len;
extern uint8_t usb_rx_buffer[USB_BUFFER_LENGTH];

void USBReceived(uint8_t* _rx_buffer);

void USBSendFire(int _bulletNum);
void USBSendHit(int _hp);
void USBSendReload(int _bulletNum,int _magNum);
void USBSend(const char* _str);

#ifdef __cplusplus
}
#endif


#endif //ARPUBG_FW_V2_INTERFACE_USE_H
