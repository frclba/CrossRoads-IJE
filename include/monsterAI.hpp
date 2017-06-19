#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include<iostream>

#include "game.hpp"
#include "components/component.hpp"
#include "components/animation_controller.hpp"
#include "math.h"

using namespace engine;

class MonsterAI : public Component{

public:
    MonsterAI(GameObject &main_game_object, std::string id, GameObject *player, AnimationControllerComponent *monster_controler):
      Component(main_game_object, id), dy(0), side(false), m_player(player), m_monster_controler(monster_controler){}
    ~MonsterAI();

    bool init();
    void update();

private:
    void gravityF();
    void processPos();
    void damage();
    void move_monster();
    void jump_monster();
    void see_player();

    const int MONSTER_MOVE = 4;
    const int ground = 552;
    const int gravity = 1;
    const float jumpF = 2;
    float dy;
    bool side;
    const bool RIGHT = true;
    const bool LEFT = false;
    bool has_damage = false;
    int life = 3;

    GameObject* m_player;
    AnimationControllerComponent* m_monster_controler;
};

#endif
