/**
    \file fireball.cpp
    This file implements the FireballController class
*/
#include "fireball.hpp"
#include "game.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
        process_fall();
        process_initial_position();
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
void FireballController::process_fall() {

    assert( _main_game_object != NULL );

    /**
        /note This line enables the fireball audio
    */
    AudioComponent* fireball_droping_audio = ( dynamic_cast<AudioComponent*>
            ( _main_game_object->get_component( "fireball_droping_audio" ) ) );

    /**
        /note This paragraph makes the fireball go down in the screen
    */
    if( ready_to_fall ) {

        /**
            /note This line represents the current velocity component by
            increasing the velocity
        */
        _main_game_object->main_positionY += variation_position_y;
        fireball_droping_audio->play(0,-1);
    }
    else {

        // Do nothing

    }
}

const int MAXIMUM_COORDINATION_Y = 850;

/**
    This method is reponsable for going from the fireball to initial position
*/
void FireballController::process_initial_position() {

    assert( _main_game_object != NULL );

    if (_main_game_object->main_positionY < MAXIMUM_COORDINATION_Y) {

        // Do nothing

    }
    else {
        _main_game_object->main_positionY = INITIAL_POSITION;
        ready_to_fall = false;
    }

}

FireballController::~FireballController(){}
