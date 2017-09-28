/**
    \file fireball.cpp
    This file implements the FireballController class
*/
#include "fireball.hpp"
#include "game.hpp"

#include <stdio.h>
#include <stdlib.h>

/**
    This method initiates the fireball in the game scene
    \return return a true value that make the fireball active
*/
bool FireballController::init() {

    /*
        last_pos_player_x = m_player->main_positionX;
        _main_game_object->main_positionX = last_pos_player_x;
    */

  return true;

}

/**
    This method is reponsable for controlling when the fireball dropps
*/
void FireballController::update() {

    if(readyToFall == true) {
        processPos();
    }
    else {
        last_pos_player_x = m_player->main_positionX;
        _main_game_object->main_positionX = last_pos_player_x;
        readyToFall = true;
    }

}

const int INITIAL_POS = -600;

/**
    This method is reponsable for the fireball dropping
*/
void FireballController::processPos() {

    AudioComponent* fireball_droping_audio = ( dynamic_cast<AudioComponent*>
            ( _main_game_object->get_component( "fireball_droping_audio" ) ) );

    if( readyToFall ) {

        // Current velocity components.

        _main_game_object->main_positionY += dy;
        fireball_droping_audio->play(0,-1);
    }
    else {

        // Do nothing

    }

    if( _main_game_object->main_positionY < 850 ) {

        // Do nothing
        
    }
    else {
        _main_game_object->main_positionY = INITIAL_POS;
        readyToFall = false; 
    }

}

FireballController::~FireballController(){}
