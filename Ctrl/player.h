//
// Created by sytnocui on 2023/11/21.
//

#ifndef ARPUBG_FW_PLAYER_H
#define ARPUBG_FW_PLAYER_H

typedef enum PlayerState{
    notConnect,
    preparing,
    battling,
    die,

}PlayerState_t;

typedef struct Player{
    int hp;
    int bullet_num;
    int mag_num;

    int damage;
    int bullet_max_num;

    PlayerState_t playerState;

    float lastFireTime;
    float FireCD;

    float lastHitTime;
    float HitCD;

    float gameTime;
}Player_t;

extern Player_t player;

void PlayerInit(Player_t* _player);
void PlayerEnterBattle(Player_t* _player);
void PlayerHitUpdate(Player_t* _player);
void PlayerFireUpdate(Player_t* _player);
void PlayerReloadUpdate(Player_t* _player);
void PlayerTimeUpdate(Player_t* _player);


#endif //ARPUBG_FW_PLAYER_H
