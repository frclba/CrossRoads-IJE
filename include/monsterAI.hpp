/**
    \file porta.hpp
    This file declares the porta class
*/
#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <iostream>
#include "game.hpp"
#include "components/component.hpp"
#include "components/animation_controller.hpp"
#include "math.h"
#include "components/audio.hpp"

using namespace engine;


/**
    \class MonsterAI
    This class is responsible through the interlligence of moster in the game
*/

class MonsterAI : public Component {

public:
    MonsterAI(GameObject &main_game_object, std::string id, GameObject *player,
              AnimationControllerComponent *monster_controler) :
              Component(main_game_object, id),vertical_position(0), side(false),
              m_player(player), m_monster_controler(monster_controler) {}

    ~MonsterAI();

    bool init();
    void update();

    void setLifePoints(int lifePoints);

    int getLifePoints();

private:

    void apply_gravity();
    void process_position();
    void receive_damage();
    void move_monster();
    void jump_monster();
    bool sees_player();
    bool has_ground();


    /**
        Sets the units which a monster can move. Ranges randomly from 1 to 2.
    */

    int horizontal_motion_units = 0;
    const int GROUND = 552;
    const int GRAVITY = 1;
    const float JUMP_SIZE = 2;

    /**
        Ranges from 552 to 0.
    */
    float vertical_position = 0;

    /**
        True: means that monster is facing right. False: means that monster is facing left.
    */
    bool side = false;
    const bool RIGHT = true;
    const bool LEFT = false;

    /**
        Indicates if monster is damaged.
    */
    bool has_damage = false;
    int life_points = 3;
    bool is_first = false;
    unsigned int time_damage = 0;
    GameObject *m_player;
    GameObject *bullet;
    GameObject *ground_obj;
    AnimationControllerComponent *m_monster_controler;

};

#endif // _MONSTER_H_
