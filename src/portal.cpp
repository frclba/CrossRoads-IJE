/**
    \file portal.cpp
    This file implements the portal class
*/
#include <portal.hpp>
#include <assert.h>

Portal::~Portal(){}

/**
    This method initiates the portal in the game scene
    \return return a true value that make the portal active
*/

bool Portal::init() {

    /*
        _main_game_object->main_positionX = 00;
        _main_game_object->main_positionY = 00;
    */

    monster_number_iterator = 0;
    time_between_monsters = 0;
    monsters_out_of_portal = 0;

    return true;

}

/**
    This method is responsible for updating portal positions in the game and for
    monsters to appear
*/
void Portal::update() {
    monster_number_iterator = (monster_number_iterator + 1) % m_monsters.size();
    apparition_of_monsters();
    horizontal_starting_position();
}

/**
    This method is responsible for time that updating portal for
    monsters to appear
*/
void Portal::apparition_of_monsters() {

    assert( Game::instance.timer != NULL );
    assert( m_monsters[monster_number_iterator] != NULL);
    assert( _main_game_object != NULL );

    if (time_between_monsters < Game::instance.timer->getTicks() &&
        m_monsters[monster_number_iterator]->state() == GameObject::State::disabled &&
        _main_game_object->main_positionX > 0 &&
        _main_game_object->main_positionX + _main_game_object->main_width < 800)
        {

        m_monsters[monster_number_iterator]->main_positionX = _main_game_object->main_positionX;
        m_monsters[monster_number_iterator]->main_positionY = _main_game_object->main_positionY;
        m_monsters[monster_number_iterator]->setState(GameObject::State::enabled);

        monsters_out_of_portal++;

        time_between_monsters = Game::instance.timer->getTicks() + 3000;
    }
    else {

        // Do nothing
    }
}

const int MAXIMUM_HORIZONTAL_POSITION = 1600;
const int MEDIUM_HORIZONTAL_POSITION = 1200;
const int MINIMUM_HORIZONTAL_POSITION = 650;

/**
    This method is responsible for updating portal horizontal positions in the game
*/
void Portal::horizontal_starting_position() {

    assert( m_background != NULL );
    assert( m_portal_pos != NULL );
    assert( _main_game_object != NULL );
    
    if( monster_number_iterator <= 5 && m_background->image_measures->x == 0 ) {
        m_portal_pos->m_horizontal_starting_position = MINIMUM_HORIZONTAL_POSITION;
    }
    else {

        // Do nothing
    }

    if( monster_number_iterator < 10 && monster_number_iterator > 5 ) {
        m_portal_pos->m_horizontal_starting_position = MEDIUM_HORIZONTAL_POSITION;
    }
    else {

        // Do nothing
    }

    if( monster_number_iterator < 20 && monster_number_iterator > 10 ) {
        m_portal_pos->m_horizontal_starting_position = MAXIMUM_HORIZONTAL_POSITION;
    }
    else {

        // Do nothing
    }

    if( monsters_out_of_portal > 20 ) {
        _main_game_object->setState(GameObject::State::disabled);
    }
    else {

        // Do nothing
    }
}

/**
    This method is responsible for add a monster no game through the portal
    @param monster specifies the monster that enters the game
*/
void Portal::add_monster( GameObject* monster ){

    assert( monster != NULL );

    monster->setState( GameObject::State::disabled );
    m_monsters.push_back( monster );

}
