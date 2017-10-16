/**
    \file monsterAI.cpp
    This file implements the MonsterAI class
*/
#include "monsterAI.hpp"
#include "game.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int PLAYER_DISTANCE = 850;
const int PLAYER_ATTACK_DISTANCE = 150;
const int MAX_SCREEN_WIDTH = 800;
const int PLAYER_DISTANCE_ITERATOR = 100;
const int TIME_STEP_ITERATOR = 1000;

int MonsterAI::getLifePoints() {
    return life_points;
}

void MonsterAI::setLifePoints(int lifePoints) {
    life_points = lifePoints;
}

/**
This method is responsible for increment the vertical position of the monster
*/
void MonsterAI::apply_gravity() {
    /*
    if(_main_game_object->main_positionY > (ground -
    _main_game_object->main_height)){
    _main_game_object->main_positionY = ground -
    _main_game_object->main_height;
}
*/
    assert(vertical_position < 40 && vertical_position > -40);

    if( !has_ground() ) {
        vertical_position += GRAVITY;
    }
    else {
        vertical_position = 0;
    }
}

/**
This method is responsible for incrementar the vertical position que monster im game
*/
void MonsterAI::process_position() {

    // std::cout<<dy<<std::endl;

    _main_game_object->main_positionY += vertical_position; // Current velocity components.
}

/**
This method is responsible for damage monster in the game for
*/
void MonsterAI::receive_damage() {

    assert(Game::instance.collision_manager != NULL);

    bullet = Game::instance.collision_manager->checkCollision(
        _main_game_object, "bullet");

    if( Game::instance.collision_manager->checkCollision(
        _main_game_object, "attack_box") || bullet ) {

            m_monster_controler->play_animation("monster_damage");

            if( bullet ) {
                bullet->setState(GameObject::State::disabled);
            }

            has_damage = true;
            if( side == RIGHT ) {

                // _main_game_object->main_positionX -= 10;

            }
            if( side == LEFT ) {

                // _main_game_object->main_positionX += 10;

            }

            assert(Game::instance.timer);

            if( Game::instance.timer->getTicks() > time_damage ) {
                setLifePoints(getLifePoints() - 1);
                time_damage = Game::instance.timer->getTicks() +
                TIME_STEP_ITERATOR;
            }
            if( getLifePoints() <= 0 ) {
                _main_game_object->setState(GameObject::State::disabled);
                setLifePoints(3);

                // Game::instance.change_scene("Win Scene");

            }
        }
        else {
            has_damage = false;
        }
}

/**
This method is responsible for move monster in direction the player in the game

*/
void MonsterAI::move_monster() {

    bool seeing_player = sees_player();

    assert(m_player != NULL);

    if( seeing_player && !has_damage &&
        m_player->main_positionX > _main_game_object->main_positionX ) {
            m_monster_controler->flipping(true);
            _main_game_object->main_positionX += horizontal_motion_units;
    }

    if( seeing_player && !has_damage &&
        m_player->main_positionX < _main_game_object->main_positionX ) {
            m_monster_controler->flipping(false);
            _main_game_object->main_positionX -= horizontal_motion_units;
    }
}

/**
    This method is responsible for possibility the monster jump in the game
*/
void MonsterAI::jump_monster() {

    // Monster jump

    assert(Game::instance.collision_manager != NULL);

    bool on_ground = Game::instance.collision_manager->checkCollision(m_player,
                      "ground");

    if( sees_player() && on_ground &&
        _main_game_object->main_positionY > m_player->main_positionY ) {
        vertical_position -= JUMP_SIZE;
    }
}

/**
    This method is responsible for possibility the monster to see player in the game
    \return return true for prayer see and false see not player
*/
bool MonsterAI::sees_player() {

    if( fabs(_main_game_object->main_positionX - m_player->main_positionX) <=
        PLAYER_DISTANCE - PLAYER_DISTANCE_ITERATOR ) {
        return true;
    }
    else {
        return false;
    }
}

/**
    This method is responsible for if you have floor to monster floor
*/
bool MonsterAI::has_ground() {

    assert(Game::instance.collision_manager != NULL);

    ground_obj = Game::instance.collision_manager->checkCollision(
                 _main_game_object, "ground");

    if( ground_obj && vertical_position >= 0 ) {
        if( vertical_position > 0 ) {
            _main_game_object->main_positionY = ground_obj->main_positionY -
            _main_game_object->main_height;
        }

        return true;
    }

    return false;
}


/**
    This method initiates the Class MonsterAI in the game
    \return return a true value that make the MonsterAI active
*/
bool MonsterAI::init() {

    _main_game_object->main_positionY = GROUND - _main_game_object->main_height;
    _main_game_object->main_positionX = 400;
    horizontal_motion_units = ( rand() % 3 ) + 1;
    setLifePoints(2);

    return true;
}

/**
    This method is responsible for updating the monster in walk and attack que monster in the game.
*/
void MonsterAI::update() {

    assert(_main_game_object != NULL);

    m_monster_controler->play_animation("monster_walk", true);

    apply_gravity();

    move_monster();
    receive_damage();
    process_position();
    jump_monster();

    if( _main_game_object->main_positionX < 0 ||
        _main_game_object->main_positionX +
        _main_game_object->main_width > MAX_SCREEN_WIDTH ) {
        _main_game_object->setState(GameObject::State::disabled);
    }

    if( Game::instance.collision_manager->checkCollision(
        _main_game_object, "player") ) {
        m_monster_controler->play_animation("monster_attack");
    }
}

MonsterAI::~MonsterAI() {}
