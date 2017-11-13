/**
    \file fireball.cpp
    This file implements the FireballController class
*/
#include "fireball.hpp"
#include "game.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Numbers defined in a standard format during all code
const int NULL_OBJECT = -3; 
const int SUCCESS = 1;
const int LIMITED_EXCEEDED = -7;

// This method is reponsable to log attempts of changing fireball attributes.
void valid_fireball_animations(int validation_code, std::string method_name){ 
 
    if(validation_code == NULL_OBJECT){ 
        Log::instance.error("Could not change a fireball attribute in method: '"
            + method_name + "', because an attribute was NULL"); 
    }
    else if(validation_code == LIMITED_EXCEEDED){ 
        Log::instance.error("Could not change a fireball attribute in method: '"
            + method_name + "', because an attribute EXCEEDED a value LIMIT");
    }
    else if(validation_code == SUCCESS){ 
        Log::instance.info("Fireball attributes changed in method: ."
            + method_name); 
    }
 
}

/**
    This method initiates the fireball in the game scene
    \return return a true value that make the fireball active
*/
bool FireballController::init() {

    /*
        last_position_player_x = m_player->main_positionX;
        _main_game_object->main_positionX = last_position_player_x;
    */

  return true;

}

/**
    This method is reponsable for controlling when the fireball dropps
*/
void FireballController::update() {

    assert( _main_game_object != NULL );

    if(ready_to_fall == true) {
        fall_process();
        initial_position_process();
        valid_fireball_animations(SUCCESS, "FireballController::update");
    }

    /**
        /note This paragraph checks if the player is in the fireball drop area
    */
    else {
        last_position_player_x = m_player->main_positionX;
        _main_game_object->main_positionX = last_position_player_x;
        ready_to_fall = true;
    }

}

// Initial position of fireball
const int INITIAL_POSITION = -600;

/**
    This method is reponsable for the fireball dropping
*/
void FireballController::fall_process() {

    assert( _main_game_object != NULL );

    /**
        /note This line enables the fireball audio
    */
    AudioComponent* fireball_droping_audio = ( dynamic_cast<AudioComponent*>
            ( _main_game_object->get_component( "fireball_droping_audio" ) ) );

    /**
        /note This paragraph makes the fireball go down in the screen
    */
    Log::instance.info("Adding fireball audio to AudioComponent.");

    if( ready_to_fall ) {

        /**
            /note This line represents the current velocity component by
            increasing the velocity
        */
        _main_game_object->main_positionY += variation_position_y;
        fireball_droping_audio->play(0,-1);
        valid_fireball_animations(SUCCESS, "FireballController::fall_process");
    }
    else {
        valid_fireball_animations(NULL_OBJECT, "FireballController::fall_process");
    }

}

const int MAXIMUM_COORDINATION_Y = 850;

/**
    This method is reponsable for going from the fireball to initial position
*/
void FireballController::initial_position_process() {

    assert( _main_game_object != NULL );

    if (_main_game_object->main_positionY >= MAXIMUM_COORDINATION_Y) {
        _main_game_object->main_positionY = INITIAL_POSITION;
        ready_to_fall = false;
        valid_fireball_animations(SUCCESS, "FireballController::initial_position_process");
    }
    else {
        valid_fireball_animations(LIMITED_EXCEEDED, "FireballController::initial_position_process");
    }

}

FireballController::~FireballController(){}
