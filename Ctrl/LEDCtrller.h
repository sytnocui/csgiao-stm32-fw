//
// Created by sytnocui on 2024/4/2.
//

#ifndef ARPUBG_FW_LEDCTRLLER_H
#define ARPUBG_FW_LEDCTRLLER_H


#include <list>
#include <cstdint>

using namespace std;

typedef void (*BtnCallback)(void*);

//typedef struct LED {
//    uint16_t ticks;  //计时器
//    uint8_t  repeat : 4;
//    uint8_t  event : 4;  //当前的状态是哪一个
//    uint8_t  active_level : 1;  //是高电平亮还是低电平亮
//    uint8_t  led_level : 1;     //当前led的电平
//    uint8_t  button_id;
//    //TODO：存GPIO和引脚数，在构造函数的时候直接传进去
//    BtnCallback  cb[number_of_event]; //TODO:led不需要设置回调，但要有个指向存储
//    struct LED* next;
//}LED;

typedef enum {
    DISACTIVE = 0, //常灭
    ACTIVE,    //常亮
    SLOW_FLASH, //慢闪
    FAST_FLASH, //快闪
    SINGLE_PULSE, // 单闪
    DOUBLE_PULSE, // 双闪
    UNITED_FLOWING, // 多LED流水灯
    number_of_event
}LedEvent;


class LEDCtrller{
    static list<int> list1;

};




#endif //ARPUBG_FW_LEDCTRLLER_H
