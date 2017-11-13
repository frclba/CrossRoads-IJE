/**
    \file bossAI.cpp
    This file implements the Boss class
*/
#include <assert.h>
#include"bossAI.hpp"

/**
    This method initiates the boss in the game scene
    \return return a true value that make the boss active
*/
bool Boss::init() {

    boss_life = 10;
    boss_update_time = 0;
    boss_movement_time_gap = 0;
    fireball_time_gap = 0;
    is_in_corner = false;

    return true;

}

/**
    This method is reponsable for update Boss positions and life and controll
    attacks
*/
void Boss::update() {

    assert(m_boss_animation != NULL);

    m_boss_animation->play_animation("boss_idle", true);

    // if the boss component is on a valid horizontal position 
    if( _main_game_object->main_positionX > -10 &&
        _main_game_object->main_positionX +
        _main_game_object->main_width < 850 ) {
        // if boss is performing a dash attack, updates its position.
        if( is_dash_attacking ) {
            boss_move();
        } 
        else {

            // Do nothing

        }

        m_boss_animation->flipping(!is_in_corner);
        // if it is time for updating boss component
        if( boss_update_time < Game::instance.timer->getTicks() ) {

            if( m_player->main_positionY > 300 ) {
                is_dash_attacking = true;
                is_fireball_attacking = false;
                m_fireball->setState(GameObject::State::disabled);
            } // if 
            else {
                is_dash_attacking = false;
                is_fireball_attacking = true;
                m_boss_animation->play_animation("boss_howl");
                m_fireball->setState(GameObject::State::enabled);
            } // else

            boss_update_time = Game::instance.timer->getTicks() + 3000;
        } // if
        else {

            // Do nothing

        }

        boss_damage();
    }
    else {

        // Do nothing

    }

}

/**
    This method is responsible for dectecting the damage to the boss life
*/
void Boss::boss_damage() {

    assert(_main_game_object != NULL);


    AudioComponent * boss_in_rage_audio = (dynamic_cast<AudioComponent*> (
                                               _main_game_object->get_component(
                                               "boss_in_rage_audio")));
  
    // if the boss is being attacked , reduces boss life points.
    if( Game::instance.collision_manager->checkCollision(
        _main_game_object, "attack_box") ||
        Game::instance.collision_manager->checkCollision(
        _main_game_object, "bullet") ) {
        
        // checks and updates the time that boss calcutes its damage
        if( damage_time < Game::instance.timer->getTicks() ) {
            boss_life--;
            damage_time = Game::instance.timer->getTicks() + 1000;
        }
        else {

            // Do nothing

        }

        if( boss_life == 3 ) {
            boss_in_rage_audio->play(0, -1);
        }
        else {

            // Do nothing

        }

        if( boss_life <= 0 ) {
            Game::instance.change_scene("Win Scene");
        }
        else {

            // Do nothing

        }
    }

}

/**
    This method is responsible for changing the boss movement in the screen
*/
void Boss::boss_move() {

    assert(_main_game_object != NULL);
    assert(m_boss_animation != NULL);


    AudioComponent *boss_dash_audio = (dynamic_cast<AudioComponent*> (
                                       _main_game_object->get_component(
                                       "boss_dash_audio")));

    assert(boss_dash_audio != NULL);

    boss_dash_audio->play(0, -1);

    m_boss_animation->play_animation("boss_dash", true);
    
    // checks if it is time for updating the delay between the boss component movement.
    if( boss_movement_time_gap < Game::instance.timer->getTicks() ) {
        // is_in_corner = !is_in_corner;
        boss_movement_time_gap = Game::instance.timer->getTicks() + 900;
    }
    else {

        // Do nothing

    }

    assert(m_position != NULL);

    if( is_in_corner ) {
        m_position->m_horizontal_starting_position -=10;
    }
    else {
        m_position->m_horizontal_starting_position +=10;
    }

    if( _main_game_object->main_positionX <=10 && is_in_corner ) {
        is_in_corner = !is_in_corner;
        is_dash_attacking = false;
    }
    else {

        // Do nothing

    }

    if( _main_game_object->main_positionX +
        _main_game_object->main_width >= 800 && !is_in_corner ) {
        is_in_corner = !is_in_corner;
        is_dash_attacking = false;
    }
    else {

        // Do nothing

    }

}

Boss::~Boss() {}
