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

    GameObject *player;
    GameObject *plataform;
    GameObject *monster;

    bool side;
    bool attack_meele;
    bool attack_ranged;

    int life_points;

private:

    const bool RIGHT = true;
    const bool LEFT = false;

    AnimationControllerComponent *animCtrl;
    AnimationControllerComponent *monster_controler;

    unsigned int jumptime;
    unsigned int time_attack;

    bool stand;
    bool jump;
    bool walkR;
    bool walkL;
    bool damageBool;

    GameObject *ground;
    GameObject* m_attack_box;

    float dy;

    ImageComponent* m_background;

};

#endif // __PLAYER_HPP__
