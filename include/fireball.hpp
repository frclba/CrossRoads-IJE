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
          variation_position_y( velocity ),
          m_player( player ),
          last_position_player_x( 0 ),
          ready_to_fall(false){}

    ~FireballController();

    bool init();

    void update();

private:
    void processPos();

    // Gravity applied to fireball
    const int gravity = 1;

    // Variation of y positon of the object
    double variation_position_y = 0.0;

    // Player of current game
    GameObject *m_player = NULL;

    // Last position of Player on the x axis
    int last_position_player_x = 0;
    
    // Boolean to enable fall action
    bool ready_to_fall = false;
};

#endif  // _FIREBALL_HPP_
