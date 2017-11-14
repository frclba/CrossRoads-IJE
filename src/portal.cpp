/**
    \file portal.cpp
    This file implements the portal class
*/
#include <portal.hpp>
#include <assert.h>

// Numbers defined in a standard format during all code
const int SUCCESS = 1;
const int LIMITED_EXCEEDED = -7;

// This method is reponsable to log attempts of changing fireball attributes.
void valid_portal_animations(int validation_code, std::string method_name){

    /**
        Print log accordding with validation code.
    */
    if (validation_code == LIMITED_EXCEEDED){

        Log::instance.error("Could not change a portal attribute in method: '" 
        + method_name + "', because an attribute EXCEEDED a value LIMIT");
    }
    else if (validation_code == SUCCESS)
    {
        Log::instance.info("Portal attributes changed in method: ." 
        + method_name);
    }
}

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

    Log::instance.info("Adding monsters through portal.");

    /**
         /note This paragraph is responsible for counting
            the time of appearance between each monster outside the portal.
    */
    if (time_between_monsters < Game::instance.timer->getTicks() &&
        m_monsters[monster_number_iterator]->state() == GameObject::State::disabled &&
        _main_game_object->main_positionX > 0 &&
        _main_game_object->main_positionX + 
        _main_game_object->main_width < 800) {

        /**
            /note This lines is responsible to set 
                position horizontal and vertical of monsters.
        */

        // This line assigns horizontal position of monsters.
        m_monsters[monster_number_iterator]->main_positionX = _main_game_object->main_positionX;

        // This line assigns vertical position of monsters.
        m_monsters[monster_number_iterator]->main_positionY = _main_game_object->main_positionY;

        // This line enable monsters.
        m_monsters[monster_number_iterator]->setState(GameObject::State::enabled);

        // This line increases the number of monsters outside the portal.
        monsters_out_of_portal++;
        
        // This line assigns the time between monsters.
        time_between_monsters = Game::instance.timer->getTicks() + 3000;

        valid_portal_animations(SUCCESS, "Portal::apparition_of_monsters");
    }
    else {

        // Do nothing
    }
}

// This line assigns a maximum value to the horizontal position value.
const int MAXIMUM_HORIZONTAL_POSITION = 1600;

// This line assigns a medium value to the horizontal position value.
const int MEDIUM_HORIZONTAL_POSITION = 1200;

// This line assigns a minimum value to the horizontal position value.
const int MINIMUM_HORIZONTAL_POSITION = 650;

/**
    This method is responsible for updating portal horizontal positions in the game
*/
void Portal::horizontal_starting_position() {

    assert( m_background != NULL );
    assert( m_portal_position != NULL );
    assert( _main_game_object != NULL );

    /**
        /note This paragraph is responsible for assigning a horizontal position
            to the portal according to the monster number.
    */

    /**
        Assigning a minimum horizontal position for the portal, 
        to the monster number iterator between 0 and 5.
    */
    if( monster_number_iterator <= 5 && m_background->image_measures->x == 0 ) {
        m_portal_position->m_horizontal_starting_position = MINIMUM_HORIZONTAL_POSITION;

        valid_portal_animations(SUCCESS, "Portal::horizontal_starting_position");
    }
    else {

        // Do nothing
    }
    /**
        Assigning a medium horizontal position for the portal, 
        to the monster number iterator between 5 and 10.
    */
    if( monster_number_iterator < 10 && monster_number_iterator > 5 ) {
        m_portal_position->m_horizontal_starting_position = MEDIUM_HORIZONTAL_POSITION;

        valid_portal_animations(SUCCESS, "Portal::horizontal_starting_position");        
    }
    else {

        // Do nothing
    }

    /**
        Assigning a maximum horizontal position for the portal, 
        to the monster number iterator between 10 and 20.
    */
    if( monster_number_iterator < 20 && monster_number_iterator > 10 ) {
        m_portal_position->m_horizontal_starting_position = MAXIMUM_HORIZONTAL_POSITION;

        valid_portal_animations(SUCCESS, "Portal::horizontal_starting_position");
    }
    else {

        // Do nothing
    }

    /**
        Print log accordding for monster number iterator over 20.
    */
    if( monsters_out_of_portal > 20 ) {
        _main_game_object->setState(GameObject::State::disabled);

        valid_portal_animations(LIMITED_EXCEEDED, "Portal::horizontal_starting_position");
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

    valid_portal_animations(SUCCESS, "Portal::add_monster");
}
