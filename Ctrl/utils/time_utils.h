#ifndef REF_STM32F4_TIME_UTILS_H
#define REF_STM32F4_TIME_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

// TODO:这几个函数是干啥的来着
uint32_t micros(void);
uint32_t millis(void);
void delayMicroseconds(uint32_t us);


void delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif
#endif //REF_STM32F4_TIME_UTILS_H
