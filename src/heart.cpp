/**
    \file heart.cpp
    This file implements the Heart class
*/
#include "heart.hpp"

Heart::~Heart() {}

/**
    This method initiates the hearts that show player's life
    \return return a true value that make the hearts active
*/
bool Heart::init() {

    /// \note initialize life points.
    _main_game_object->setState(GameObject::State::enabled);

    return true;

}

/**
    This method updates the quantity of hearts according to player's life
*/
void Heart::update() {

    /** 
        \note This paragraph is responsible to update the actual points of
            life of the player. 
    */
    if( m_life > m_player->get_life_points() ) {
        _main_game_object->setState(GameObject::State::disabled);
    }
    else {
        // Do nothing
    }

}
