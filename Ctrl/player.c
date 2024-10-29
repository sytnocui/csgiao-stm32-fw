//
// Created by sytnocui on 2023/11/21.
//

#include "player.h"
#include "main.h"
#include "menu.h"
#include "wave.h"
#include "interface_uart.h"
#include "interface_use.h"

Player_t player;

void PlayerInit(Player_t* _player){
    _player->hp = 100;
    _player->bullet_num = 30;
    _player->mag_num = 120;

    _player->playerState = preparing;

    _player->damage = 10;
    _player->bullet_max_num = 30;

    _player->lastFireTime = 0.0f;
    _player->FireCD = 0.12f;
    _player->lastHitTime = 0.0f;
    _player->HitCD = 0.1f;

    _player->gameTime = 0.0f;
}

//ÿ�ν���ս����initһ��
void PlayerEnterBattle(Player_t* _player){
    //����״ָ̬ʾ���

    _player->hp = 100;
    _player->bullet_num = 30;
    _player->mag_num = 120;
    _player->playerState = battling;

    _player->gameTime = 0.0f;
    _player->lastFireTime = 0.0f;
    _player->lastHitTime = 0.0f;
}

//ÿ�����ս��������һ��
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

void PlayerHitUpdate(Player_t* _player){
    //���CD
    if (_player->gameTime - _player->lastHitTime <= _player->HitCD){
        return;
    }
    _player->lastHitTime = _player->gameTime;


    //����������Ҫ��ʱ��ɣ�����Ҫ���Ƿ�ս���Ƿ���
    Hit();
    PlayMusic(HIT_SOUND_DATA, HIT_SOUND_LENGTH);

    _player->hp -= 10;
    BlueToothSendHit(_player->hp);
    USBSendHit(_player->hp);

    //����ս�����˳�
    if(_player->playerState != battling){
        return;
    }

    //״̬����ֻ�п�ս��Ž���
    //�ж��Ƿ�����
    if (_player->hp <= 0){
        _player->playerState = die;
    }


}


void PlayerFireUpdate(Player_t* _player){
    //���CD
    if (_player->gameTime - _player->lastFireTime <= _player->FireCD){
        return;
    }
    _player->lastFireTime = _player->gameTime;


    //���˾��˳�
    if(_player->playerState == die){
        return;
    }

    //�жϵ�������û���ӵ�
    if (_player->bullet_num <= 0){
        PlayMusic(NOFIRE_SOUND_DATA, NOFIRE_SOUND_LENGTH);
        return;
    }

    _player->bullet_num -= 1;
    Fire(); //Ӳ��������
    PlayMusic(FIRE_SOUND_DATA, FIRE_SOUND_LENGTH);
    BlueToothSendFire(_player->bullet_num);
    USBSendFire(_player->bullet_num);

}

void PlayerReloadUpdate(Player_t* _player){
    //���˾��˳�
    if(_player->playerState == die){
        return;
    }

    //�жϵ�������û���ӵ�
    if (_player->mag_num <= 0){
        PlayMusic(NOFIRE_SOUND_DATA, NOFIRE_SOUND_LENGTH);
        return;
    }

    //��ʽ���ӵ�
    //��������ӵ�������������
    if (_player->mag_num <= _player->bullet_max_num){
        _player->bullet_num = _player->mag_num;
        _player->mag_num = 0;
    } else {
        _player->bullet_num = _player->bullet_max_num;
        _player->mag_num -= _player->bullet_max_num;
    }
    PlayMusic(RELOAD_SOUND_DATA, RELOAD_SOUND_LENGTH);
    BlueToothSendReload(_player->bullet_num,_player->mag_num);
    USBSendReload(_player->bullet_num,_player->mag_num);
}


void PlayerTimeUpdate(Player_t* _player){
    _player->gameTime += 0.005f;
}