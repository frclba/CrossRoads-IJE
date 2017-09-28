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

    unsigned int timestep = 0;
    unsigned int fireball_time = 0;
    unsigned int move_time = 0;
    unsigned int time_damage = 0;

    bool side = false;
    bool dash_attack = false;
    bool fireball_attack = false;

    unsigned int life = 0;

};

#endif // _BOSS_AI_H_
