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

    //����
    _player->defense = 0;
    _player->HitCD = 0.1f;


    //����
    _player->damage = 20;  //���������� damage û���ã�ֻ�ܸ�defense
    _player->bullet_max_num = 30;
    _player->FireCD = 0.2f;

    _player->lastFireTime = 0.0f;
    _player->lastHitTime = 0.0f;

    _player->gameTime = 0.0f;

    HAL_GPIO_WritePin(RX_LED_GPIO_Port,RX_LED_Pin,GPIO_PIN_RESET);
}

//ÿ�ν���ս����initһ��
void PlayerEnterBattle(Player_t* _player){
    //����״ָ̬ʾ���

    PlayerInit(_player);
    _player->playerState = battling;


}

//ÿ�����ս��������һ��
void PlayerQuitBattle(Player_t* _player){
    PlayerInit(_player);
}

void PlayerResurrect(Player_t* _player){
    _player->hp = 100;
    _player->playerState = battling;

    HAL_GPIO_WritePin(RX_LED_GPIO_Port,RX_LED_Pin,GPIO_PIN_RESET);
}

void PlayerDie(Player_t* _player){
    _player->hp = 0;
    _player->playerState = die;

}

void PlayerUpdateData(Player_t* _player,uint8_t* data){
    strtok(data, "|"); // ��ȡ��һ���ָ� Э����
    _player->hp = atoi(strtok(NULL, ",")); // ��ȡ��һ�����ַ���
    _player->bullet_num = atoi(strtok(NULL, ",")); // ��ȡ��һ�����ַ���
    _player->mag_num = atoi(strtok(NULL, ",")); // ��ȡ��һ�����ַ���
}

void PlayerChangeGun(Player_t* _player,uint8_t* data){
    strtok(data, "|"); // ��ȡ��һ���ָ� Э����

    _player->bullet_num = atoi(strtok(NULL, ",")); // �����ӵ���
    _player->mag_num = atoi(strtok(NULL, ",")); // ʣ���ӵ���

    _player->bullet_max_num = atoi(strtok(NULL, ",")); // ��󵯼��ӵ���
    _player->FireCD = atoff(strtok(NULL, ",")); // ����
}

void PlayerChangeArmor(Player_t* _player,uint8_t* data){
    strtok(data, "|"); // ��ȡ��һ���ָ� Э����
    _player->defense = atoi(strtok(NULL, ",")); // ÿ���ܵ����˺���
    _player->HitCD = atoff(strtok(NULL, ",")); // ����CD
}

void PlayerHitUpdate(Player_t* _player){
    //���CD
    if (_player->gameTime - _player->lastHitTime <= _player->HitCD){
        return;
    }
    _player->lastHitTime = _player->gameTime;

    //���˾��˳��������ж����ֻ�
    if(_player->playerState == die){
        return;
    }

    //����������Ҫ��ʱ��ɣ�����Ҫ���Ƿ�ս���Ƿ���
    Hit();
//    PlayMusic(HIT_SOUND_DATA, HIT_SOUND_LENGTH);

    _player->hp -= (_player->damage - _player->defense );
//    BlueToothSendHit(_player->hp);
    USBSendHit(_player->hp);

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
//        PlayMusic(NOFIRE_SOUND_DATA, NOFIRE_SOUND_LENGTH);
        return;
    }

    _player->bullet_num -= 1;
    Fire(); //Ӳ��������
//    PlayMusic(FIRE_SOUND_DATA, FIRE_SOUND_LENGTH);
//    BlueToothSendFire(_player->bullet_num);
    USBSendFire(_player->bullet_num);

}

void PlayerReloadUpdate(Player_t* _player){
    //���˾��˳�
    if(_player->playerState == die){
        return;
    }

    //�жϵ�������û���ӵ�
    if (_player->mag_num <= 0){
//        PlayMusic(NOFIRE_SOUND_DATA, NOFIRE_SOUND_LENGTH);
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
//    PlayMusic(RELOAD_SOUND_DATA, RELOAD_SOUND_LENGTH);
//    BlueToothSendReload(_player->bullet_num,_player->mag_num);
    USBSendReload(_player->bullet_num,_player->mag_num);
}


void PlayerTimeUpdate(Player_t* _player){
    _player->gameTime += 0.005f;

    if (_player->playerState == die){
        HAL_GPIO_WritePin(RX_LED_GPIO_Port,RX_LED_Pin,GPIO_PIN_SET);
    }
}