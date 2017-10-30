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
    /** 
        \note Declares the contructor, defining the initial values 
        of the player.
    */ 
    Player( GameObject &main_game_object, std::string id,
         AnimationControllerComponent *animC, GameObject &attack_box,
	       ImageComponent *background ):
         Component(main_game_object, id), animation_controller(animC),
         is_walking_right(false), is_walking_left(false),
         attack_box_dimensions(&attack_box),
         image_background(background){}

    ~Player();

    void update();

    /// \note Initialize GameObjects with NULL. 
    GameObject *player = NULL;
    GameObject *plataform = NULL;
    GameObject *monster = NULL;

    /// \note Functions of player life, attack and body direction.
    int get_life_points();
    bool get_is_attacking_ranged();
    bool get_direction_boby_side();

private:
    bool init();

    bool has_ground();

    void is_dead();

    void detect_boby_side();

    /**
        \note This paragraph declare functions to update, detect and apply
            player attack.
    */
    void update_attack();
    void detect_attack_meele();
    void detect_attack_ranged();
    void apply_attack_meele();
    void apply_attack_ranged();

    /**
        \note This paragraph declare functions to update, detect and apply
            player movement.
    */
    void update_move();
    void detect_move_right();
    void detect_move_left();
    void apply_move_right();
    void apply_move_left();

    void detect_background();

    void detect_jump();

    /**
        \note This paragraph declare functions to detect an apply damege in
            player, detect low life of player and damage_player not used.
    */
    void damage_player();
    void detect_damage();
    void apply_damage();
    void detect_low_life();

    void process_position();

    void apply_gravity();

    int life_points = 5;

    /// \note Initialize types of attack variables with false.
    bool is_attacking_meele = false;
    bool is_attacking_ranged = false;

    bool direction_boby_side = false;

    /**
        Constant helps to detect if the player's body is to the right
    */
    const bool RIGHT = true;

    /**
        Constant helps to detect if the player's body is to the left
    */
    const bool LEFT = false;

    AnimationControllerComponent* animation_controller = NULL;

    /**
        Auxiliary variable referring to the time a
        player is attacking, if he exceeds the current time,
        he will not apply his attack
    */
    unsigned int time_attack = 0;

    /**
        Auxiliary variable referring to the time a
        player is taking damage, if he exceeds the current time,
        he will not take the damage
     */
    unsigned int damage_time = 0;

    /**
        Variable to detect if the player's movement is to the right
    */
    bool is_walking_right = false;
    bool is_walking_left = false;

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
