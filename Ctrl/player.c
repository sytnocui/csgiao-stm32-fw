//
// Created by sytnocui on 2023/11/21.
//

#include "player.h"
#include "main.h"
#include "menu.h"
#include "wave.h"
#include "interface_uart.h"

Player_t player;

void PlayerInit(Player_t* _player){
    _player->hp = 100;
    _player->bullet_num = 30;
    _player->mag_num = 120;

    _player->playerState = notConnect;

    _player->damage = 10;
    _player->bullet_max_num = 30;

    _player->lastFireTime = 0.0f;
    _player->FireCD = 0.15f;
    _player->lastHitTime = 0.0f;   
    _player->HitCD = 0.1f;

    _player->gameTime = 0.0f;
}

//每次进入战斗都init一下
void PlayerEnterBattle(Player_t* _player){
    //错误状态指示清空

    _player->hp = 100;
    _player->bullet_num = 30;
    _player->mag_num = 120;
    _player->playerState = battling;

    _player->gameTime = 0.0f;
}

void PlayerHitUpdate(Player_t* _player){
    //不在战斗就退出
    if(_player->playerState != battling){
        return;
    }
    if (_player->gameTime - _player->lastHitTime <= _player->HitCD){
        return;
    }
    _player->lastHitTime = _player->gameTime;
    _player->hp -= 10;
    BlueToothSendHit(_player->hp);


    //判断是否死亡
    if (_player->hp <= 0){
        _player->playerState = die;
    }

    PlayMusic(HIT_SOUND_DATA, HIT_SOUND_LENGTH);
}


void PlayerFireUpdate(Player_t* _player){
    //不在战斗就退出
    if(_player->playerState != battling){
        return;
    }
    if (_player->gameTime - _player->lastFireTime <= _player->FireCD){
        return;
    }
    _player->lastFireTime = _player->gameTime;

    //判断弹夹里有没有子弹
    if (_player->bullet_num <= 0){
        PlayMusic(NOFIRE_SOUND_DATA, NOFIRE_SOUND_LENGTH);
        return;
    }
    _player->bullet_num -= 1;
    Fire(); //硬件发激光
    PlayMusic(FIRE_SOUND_DATA, FIRE_SOUND_LENGTH);
    BlueToothSendFire(_player->bullet_num);

}

void PlayerReloadUpdate(Player_t* _player){
    //不在战斗就退出
    if(_player->playerState != battling){
        return;
    }

    //判断弹夹里有没有子弹
    if (_player->mag_num <= 0){
        PlayMusic(NOFIRE_SOUND_DATA, NOFIRE_SOUND_LENGTH);
        return;
    }

    //正式减子弹
    //如果储备子弹不够整个弹夹
    if (_player->mag_num <= _player->bullet_max_num){
        _player->bullet_num = _player->mag_num;
        _player->mag_num = 0;
    } else {
        _player->bullet_num = _player->bullet_max_num;
        _player->mag_num -= _player->bullet_max_num;
    }
    PlayMusic(RELOAD_SOUND_DATA, RELOAD_SOUND_LENGTH);
    BlueToothSendReload(_player->bullet_num,_player->mag_num);
}


void PlayerTimeUpdate(Player_t* _player){
    //不在战斗就退出
    if(_player->playerState != battling){
        return;
    }
    _player->gameTime += 0.005f;

}