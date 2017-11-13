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

    if( _main_game_object->main_positionX > -10 &&
        _main_game_object->main_positionX +
        _main_game_object->main_width < 850 ) {

        if( is_dash_attacking ) {
            move();
        }
        else {

            // Do nothing

        }

        /**
            /note This line is responsible for flipping the boss animation when
            he heachs the screen corner
        */
        m_boss_animation->flipping(!is_in_corner);

        /**
            /note This paragraph is responsible for counting the time btween
            boss status updates
        */
        if( boss_update_time < Game::instance.timer->getTicks() ) {

            if( m_player->main_positionY > 300 ) {
                is_dash_attacking = true;
                is_fireball_attacking = false;
                m_fireball->setState(GameObject::State::disabled);
            }
            else {
                is_dash_attacking = false;
                is_fireball_attacking = true;
                m_boss_animation->play_animation("boss_howl");
                m_fireball->setState(GameObject::State::enabled);
            }

            boss_update_time = Game::instance.timer->getTicks() + 3000;
        }
        else {

            // Do nothing

        }

        damage();
    }
    else {

        // Do nothing

    }

}

/**
    This method is responsible for dectecting the damage to the boss life
*/
void Boss::damage() {

    assert(_main_game_object != NULL);

    /**
        /note This line enables the boss rage audio
    */
    AudioComponent * boss_in_rage_audio = (dynamic_cast<AudioComponent*> (
                                               _main_game_object->get_component(
                                               "boss_in_rage_audio")));
     /**
        /note This paragraph is responsible for check the colision and calculate
        damage
     */
    if( Game::instance.collision_manager->checkCollision(
        _main_game_object, "attack_box") ||
        Game::instance.collision_manager->checkCollision(
        _main_game_object, "bullet") ) {

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
void Boss::move() {

    assert(_main_game_object != NULL);
    assert(m_boss_animation != NULL);


    AudioComponent *boss_dash_audio = (dynamic_cast<AudioComponent*> (
                                       _main_game_object->get_component(
                                       "boss_dash_audio")));

    assert(boss_dash_audio != NULL);

    boss_dash_audio->play(0, -1);

    m_boss_animation->play_animation("boss_dash", true);

    /**
        /note This paragraph is responsible for increasing the tie between boss
        moves
    */
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
