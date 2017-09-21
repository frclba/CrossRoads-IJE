#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <iostream>
#include "game.hpp"
#include "components/component.hpp"
#include "components/animation_controller.hpp"
#include "math.h"
#include "components/audio.hpp"

using namespace engine;

class MonsterAI : public Component {

public:
    MonsterAI(GameObject &main_game_object, std::string id, GameObject *player,
              AnimationControllerComponent *monster_controler) :
              Component(main_game_object, id), dy(0), side(false),
              m_player(player), m_monster_controler(monster_controler) {}

    ~MonsterAI();

    bool init();
    void update();

private:

    void gravityF();
    void processPos();
    void damage();
    void move_monster();
    void jump_monster();
    bool see_player();
    void bullet_damage();
    bool has_ground();

    int MONSTER_MOVE;
    const int ground = 552;
    const int gravity = 1;
    const float jumpF = 2;
    float dy;
    bool side;
    const bool RIGHT = true;
    const bool LEFT = false;
    bool has_damage = false;
    int life = 3;
    bool is_first = false;

    GameObject *m_player;
    GameObject *bullet;
    GameObject *ground_obj;
    AnimationControllerComponent *m_monster_controler;

};

#endif // _MONSTER_H_
