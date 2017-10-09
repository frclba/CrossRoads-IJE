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
         Component(main_game_object, id), direction_boby_side(false),
         is_attacking_meele(false), is_attacking_ranged(false), animation_controller(animC),
         stand(false), is_jumping(false), is_walking_right(false), is_walking_left(false),
         is_taking_damage(false),  attack_box_dimensions(&attack_box),
         image_background(background){}

    ~Player();

    bool init();
    bool has_ground();

    void update();
    void is_dead();
    void damage_player();
    void update_attack();
    void detect_boby_side();
    void detect_attack_meele();
    void detect_attack_ranged();
    void apply_attack_meele();
    void apply_attack_ranged();
    void update_move();
    void detect_move_right();
    void detect_move_left();
    void apply_move_right();
    void apply_move_left();
    void detect_background();
    void detect_jump();
    void detect_damage();
    void process_position();
    void apply_gravity();

    GameObject *player = NULL;
    GameObject *plataform = NULL;
    GameObject *monster = NULL;

    bool direction_boby_side = false;

    bool is_attacking_meele = false;
    bool is_attacking_ranged = false;

    int life_points = 5;

private:

    /**
        Constant helps to detect if the player's body is to the right
    */
    const bool RIGHT = true;

    /**
        Constant helps to detect if the player's body is to the left
    */
    const bool LEFT = false;

    AnimationControllerComponent* animation_controller = NULL;
    AnimationControllerComponent* monster_controller = NULL;

    unsigned int time_jump = 0;

    /**
        Auxiliary variable referring to the time a
        player is attacking, if he exceeds the current time,
        he will not apply his attack
    */
    unsigned int time_attack = 0;

    bool stand = false;
    bool is_jumping = false;

    /**
        Variable to detect if the player's movement is to the right
    */
    bool is_walking_right = false;
    bool is_walking_left = false;
    bool is_taking_damage = false;

    /**
        Object instance that helps to check if have terrain where the player is
    */
    GameObject* get_ground_collision = NULL;

    /**
        Object instance that defines player's attack dimensions, in height,
        width and positions in coordinates x,y. y ranges from 522 to 0. x can
        vary within scence boundaries.
    */
    GameObject* attack_box_dimensions = NULL;

    /**
        Current coordinate y of player position
    */
    float vertical_position = 0;

    /**
        Object instance to get the component of the image to verify that
        the player has reached the bottom
    */
    ImageComponent* image_background = NULL;

};

#endif // __PLAYER_HPP__
