/**
  \file player.hpp
  This file declares the Player class, his methods and attributes with their
  encapsulation.
*/

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <iostream>

#include "components/component.hpp"
#include "components/animation_controller.hpp"
#include "components/image.hpp"
#include "components/audio.hpp"

#include "game.hpp"
#include "Logger.hpp"

using namespace engine;

/// This class represents the player, their characteristics and behavior
/**
    \class Player
    Class responsable for all logic about the player.
*/
class Player : public Component {

public:

    Player( GameObject &main_game_object, std::string id,
         AnimationControllerComponent *animC, GameObject &attack_box,
	       ImageComponent *background ):
         Component(main_game_object, id), side(false),
         attack_meele(false), attack_ranged(false), animCtrl(animC),
         stand(false), jump(false), walkR(false), walkL(false),
         damageBool(false),  m_attack_box(&attack_box),
         m_background(background){}

    ~Player();

    bool init();
    bool has_ground();

    void update();
    void is_dead();
    void damage_player();
    void attack_player();
    void move_player();
    void jump_player();
    void damage();
    void processPos();
    void gravityF();

    GameObject *player = NULL;
    GameObject *plataform = NULL;
    GameObject *monster = NULL;

    bool side = false;
    bool attack_meele = false;
    bool attack_ranged = false;

    int life_points = 5;

private:

    const bool RIGHT = true;
    const bool LEFT = false;

    AnimationControllerComponent *animCtrl = NULL;
    AnimationControllerComponent *monster_controler = NULL;

    unsigned int jumptime = 0;
    unsigned int time_attack = 0;

    bool stand = false;
    bool jump = false;
    bool walkR = false;
    bool walkL = false;
    bool damageBool = false;

    GameObject *ground = NULL;
    GameObject* m_attack_box = NULL;

    float dy = 0;

    ImageComponent* m_background = NULL;

};

#endif // __PLAYER_HPP__
