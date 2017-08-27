#ifndef _BOSS_AI_H_
#define _BOSS_AI_H_

#include <iostream>
#include "game.hpp"
#include "components/component.hpp"
#include "components/animation_controller.hpp"
#include "cameraposition.hpp"
#include "components/audio.hpp"

using namespace engine;

class Boss : public Component {

public:

    Boss(GameObject &main_game_object,
         std::string id,
         AnimationControllerComponent* boss_animation,
         GameObject* fireball,CameraPosition* positon,
         GameObject* player):
         Component(main_game_object, id),
         m_boss_animation(boss_animation),
         m_fireball(fireball),
         m_position(positon),
         m_player(player) {}

    ~Boss();

    bool init();
    void update();
    void boss_move();

private:

    void boss_damage();

    AnimationControllerComponent *m_boss_animation;
    GameObject *m_fireball;
    CameraPosition *m_position;
    GameObject *m_player;

    unsigned int timestep;
    unsigned int fireball_time;
    unsigned int move_time;
    unsigned int time_damage;


    bool side;
    bool dash_attack;
    bool fireball_attack;

    unsigned int life;

};

#endif // _BOSS_AI_H_
