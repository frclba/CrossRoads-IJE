/**
    \file bossAI.hpp
    This file declares the Boss class
*/

#ifndef _BOSS_AI_H_
#define _BOSS_AI_H_

#include <iostream>
#include "game.hpp"
#include "components/component.hpp"
#include "components/animation_controller.hpp"
#include "cameraposition.hpp"
#include "components/audio.hpp"

using namespace engine;

/**
    \class bossAI
    This class is responsible for Boss movement and behavior
*/
class Boss : public Component {

public:

    Boss( GameObject &main_game_object, std::string id,
         AnimationControllerComponent *boss_animation, GameObject *fireball,
         CameraPosition *positon, GameObject *player ):
        Component( main_game_object, id ), m_boss_animation( boss_animation ),
        m_fireball( fireball ), m_position( positon ), m_player( player ){}

    ~Boss();

    bool init();
    void update();
    void boss_move();

private:

    void boss_damage();

    AnimationControllerComponent *m_boss_animation = NULL;
    GameObject *m_fireball = NULL;
    CameraPosition *m_position = NULL;
    GameObject *m_player = NULL;

    /**
        This attribute counts the delay between boss status updating
    */
    unsigned int boss_update_time = 0;

    /**
        This attribute represents the time delay btween fireball attacks
    */
    unsigned int fireball_time_gap = 0;

    /**
        This attribute represents the time delay btween boss movements
    */
    unsigned int boss_movement_time_gap = 0;

    /**
        This attribute count the time to calculate how much damage the boss
        is receiving
    */
    unsigned int damage_time = 0;

    /**
        This attribute signals if the boss animation needs to change direction
    */
    bool is_in_corner = false;

    /**
        This attribute signals the boss state
    */
    bool is_dash_attacking = false;

    /**
        This attribute signals the boss state
    */
    bool is_fireball_attacking = false;

    /**
        This attribute counts the boss life and goes from 10 to 0
    */
    unsigned int boss_life = 0;

};

#endif // _BOSS_AI_H_
