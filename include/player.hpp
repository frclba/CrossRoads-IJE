#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__
#include <iostream>

#include "components/component.hpp"
#include "components/animation_controller.hpp"
#include "game.hpp"
#include "Logger.hpp"

using namespace engine;

class Player : public Component{
public:
  Player(GameObject &_main_game_object, std::string component_id, AnimationControllerComponent *animC,GameObject &attack_box ):
    Component(_main_game_object,component_id), animCtrl(animC),m_attack_box(&attack_box),
    walkR(false), walkL(false), jump(false), stand(false), attack(false), damageBool(false),side(false){}

    ~Player();

    bool init();
    void update();

    void is_dead();
    void damage_player();
    void attack_player();
    void move_player();
    void jump_player();
    void damage();


    void processPos();
    void gravityF();
    bool has_ground();
    //void monsterAI(GameObject *obj);

    GameObject *player;
    GameObject *plataform;
    GameObject *monster;

private:
    const bool RIGHT = true;
    const bool LEFT = false;
    AnimationControllerComponent *animCtrl;
    AnimationControllerComponent *monster_controler;
    unsigned int jumptime;
    bool walkR;
    bool walkL;
    bool jump;
    bool stand;
    bool attack;
    bool damageBool;
    bool side;
    GameObject *ground;
    GameObject* m_attack_box;
    float dy;
};

#endif
