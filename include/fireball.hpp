/**
    \file fireball.hpp
    This file declares the FireballController class
*/
#ifndef _FIREBALL_HPP_
#define _FIREBALL_HPP_

#include<iostream>

#include "game.hpp"
#include "components/component.hpp"
#include "components/animation_controller.hpp"
#include "components/audio.hpp"
#include "math.h"

using namespace engine;

/**
    \class FireballController
    This class is responsible for the behavior of fireball attacks
*/
class FireballController : public Component{

public:
    FireballController( GameObject &main_game_object, std::string id,
                       double velocity, GameObject *player ):
          Component( main_game_object, id ),
          dy( velocity ),
          m_player( player ),
          last_pos_player_x( 0 ),
          readyToFall(false){}

    ~FireballController();

    bool init();

    void update();

private:
    void processPos();

    const int GRAVITY = 1;

    double dy;

    GameObject *m_player;

    int last_pos_player_x;

    bool readyToFall;
};

#endif  // _FIREBALL_HPP_
