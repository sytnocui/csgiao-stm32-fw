//
// Created by sytnocui on 2023/11/21.
//

#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "main.h"
#include "menu.h"

#include "interface_use.h"

Player_t player;

void PlayerInit(Player_t* _player){
    _player->hp = 100;
    _player->bullet_num = 30;
    _player->mag_num = 120;

    _player->playerState = preparing;

    //护甲
    _player->damage = 20;
    _player->HitCD = 0.1f;


    //武器
    _player->bullet_max_num = 30;
    _player->FireCD = 0.15f;



    _player->lastFireTime = 0.0f;
    _player->lastHitTime = 0.0f;


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
    _player->lastFireTime = 0.0f;
    _player->lastHitTime = 0.0f;
}

//每次完成战斗都运行一次
void PlayerQuitBattle(Player_t* _player){
    _player->hp = 100;
    _player->bullet_num = 30;
    _player->mag_num = 120;
    _player->playerState = preparing;

    _player->gameTime = 0.0f;
    _player->lastFireTime = 0.0f;
    _player->lastHitTime = 0.0f;

}

void PlayerResurrect(Player_t* _player){
    _player->hp = 100;
    _player->bullet_num = 30;
    _player->mag_num = 120;
    _player->playerState = battling;

}

void PlayerDie(Player_t* _player){
    _player->hp = 0;
    _player->playerState = die;

}

void PlayerUpdateData(Player_t* _player,uint8_t* data){
    strtok(data, "|"); // 获取第一个分隔 协议名
    _player->hp = atoi(strtok(NULL, ",")); // 获取下一个子字符串
    _player->bullet_num = atoi(strtok(NULL, ",")); // 获取下一个子字符串
    _player->mag_num = atoi(strtok(NULL, ",")); // 获取下一个子字符串
}

void PlayerChangeGun(Player_t* _player,uint8_t* data){
    strtok(data, "|"); // 获取第一个分隔 协议名

    _player->bullet_num = atoi(strtok(NULL, ",")); // 弹夹子弹数
    _player->mag_num = atoi(strtok(NULL, ",")); // 剩余子弹数

    _player->bullet_max_num = atoi(strtok(NULL, ",")); // 最大弹夹子弹数
    _player->FireCD = atoff(strtok(NULL, ",")); // 射速
}

void PlayerChangeArmor(Player_t* _player,uint8_t* data){
    strtok(data, "|"); // 获取第一个分隔 协议名
    _player->damage = atoi(strtok(NULL, ",")); // 每次受到的伤害数
    _player->HitCD = atoff(strtok(NULL, ",")); // 免伤CD
}

void PlayerHitUpdate(Player_t* _player){
    //检查CD
    if (_player->gameTime - _player->lastHitTime <= _player->HitCD){
        return;
    }
    _player->lastHitTime = _player->gameTime;

    //死了就退出，死亡判断在手机
    if(_player->playerState == die){
        return;
    }

    //基础反馈需要随时完成，不需要管是否开战，是否存活
    Hit();
//    PlayMusic(HIT_SOUND_DATA, HIT_SOUND_LENGTH);

    _player->hp -= 10;
//    BlueToothSendHit(_player->hp);
    USBSendHit(_player->hp);

}


void PlayerFireUpdate(Player_t* _player){
    //检查CD
    if (_player->gameTime - _player->lastFireTime <= _player->FireCD){
        return;
    }
    _player->lastFireTime = _player->gameTime;


    //死了就退出
    if(_player->playerState == die){
        return;
    }

    //判断弹夹里有没有子弹
    if (_player->bullet_num <= 0){
//        PlayMusic(NOFIRE_SOUND_DATA, NOFIRE_SOUND_LENGTH);
        return;
    }

    _player->bullet_num -= 1;
    Fire(); //硬件发激光
//    PlayMusic(FIRE_SOUND_DATA, FIRE_SOUND_LENGTH);
//    BlueToothSendFire(_player->bullet_num);
    USBSendFire(_player->bullet_num);

}

void PlayerReloadUpdate(Player_t* _player){
    //死了就退出
    if(_player->playerState == die){
        return;
    }

    //判断弹夹里有没有子弹
    if (_player->mag_num <= 0){
//        PlayMusic(NOFIRE_SOUND_DATA, NOFIRE_SOUND_LENGTH);
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
//    PlayMusic(RELOAD_SOUND_DATA, RELOAD_SOUND_LENGTH);
//    BlueToothSendReload(_player->bullet_num,_player->mag_num);
    USBSendReload(_player->bullet_num,_player->mag_num);
}


void PlayerTimeUpdate(Player_t* _player){
    _player->gameTime += 0.005f;
}