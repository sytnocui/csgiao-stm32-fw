#ifndef __SOUND_DATA_H__
#define __SOUND_DATA_H__

#include <stdint-gcc.h>

#define FIRE_SOUND_LENGTH	1
#define NOFIRE_SOUND_LENGTH	1
#define HIT_SOUND_LENGTH	1
#define RELOAD_SOUND_LENGTH	1


extern uint8_t FIRE_SOUND_DATA[FIRE_SOUND_LENGTH];
extern uint8_t NOFIRE_SOUND_DATA[NOFIRE_SOUND_LENGTH];
extern uint8_t HIT_SOUND_DATA[HIT_SOUND_LENGTH];
extern uint8_t RELOAD_SOUND_DATA[RELOAD_SOUND_LENGTH];

void PlayMusic(uint8_t* _address, int _len);

#endif
