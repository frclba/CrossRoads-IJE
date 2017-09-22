/**
    \file monsterAI.cpp
    This file implements the MonsterAI class
*/
#include "monsterAI.hpp"
#include "game.hpp"
#include <stdio.h>
#include <stdlib.h>

unsigned int time_damage;

const int PLAYER_DISTANCE = 850;
const int PLAYER_ATTACK_DISTANCE = 150;

/**
    This method initiates the Class MonsterAI in the game
    \return return a true value that make the MonsterAI active
*/
bool MonsterAI::init() {

    _main_game_object->main_positionY = ground - _main_game_object->main_height;
    _main_game_object->main_positionX = 400;
    MONSTER_MOVE = ( rand() % 3 ) + 1;
    life = 2;

    return true;

}

/**
    This method is responsible for updating the monster in walk and attack que monster in the game.
*/
void MonsterAI::update() {

   
    gravityF();

    move_monster();
    damage();
    processPos();
    jump_monster();


    if( _main_game_object->main_positionX < 0 ||
        _main_game_object->main_positionX +
        _main_game_object->main_width > 800 ) {
        _main_game_object->setState(GameObject::State::disabled);
    }

     m_monster_controler->play_animation("monster_walk", true);

    if( Game::instance.collision_manager->checkCollision(
        _main_game_object, "player") ) {
        m_monster_controler->play_animation("monster_attack");
    }

}
/**
    This method is responsible for possibility the monster to see player in the game
    \return return true for prayer see and false see not player
*/

bool MonsterAI::see_player() {

    if( fabs(_main_game_object->main_positionX - m_player->main_positionX) <=
        PLAYER_DISTANCE - 100 ) {
        return true;
    }
    else {
        return false;
    }

}


/**
    This method is responsible for possibility the monster jump in the game
    
*/

void MonsterAI::jump_monster() {

    // Monster jump

    bool isOnGround = Game::instance.collision_manager->checkCollision(m_player,
                      "ground");

    if( see_player() && isOnGround &&
        _main_game_object->main_positionY > m_player->main_positionY ) {
        dy -= jumpF;
    }

}

/**
    This method is responsible for move monster in direction the player in the game
    
*/

void MonsterAI::move_monster() {

    bool isSee = see_player();

    if( isSee && !has_damage &&
        m_player->main_positionX > _main_game_object->main_positionX ) {
        m_monster_controler->flipping(true);
        _main_game_object->main_positionX += MONSTER_MOVE;
    }

    if( isSee && !has_damage &&
        m_player->main_positionX < _main_game_object->main_positionX ) {
        m_monster_controler->flipping(false);
        _main_game_object->main_positionX -= MONSTER_MOVE;
    }

}

/**
    This method is responsible for incrementar the vertical position que monster im game
*/

void MonsterAI::processPos() {

     // std::cout<<dy<<std::endl;

    _main_game_object->main_positionY += dy; // Current velocity components.

}

/**
    This method is responsible for increment the vertical position of the monster
*/

void MonsterAI::gravityF() {

    /*
        if(_main_game_object->main_positionY > (ground -
             _main_game_object->main_height)){
            _main_game_object->main_positionY = ground -
            _main_game_object->main_height;
        }
    */

    if( !has_ground() ) {
        dy += gravity;
    }
    else {
        dy = 0;
    }

}

/**
    This method is responsible for if you have floor to monster floor
*/

bool MonsterAI::has_ground() {

    ground_obj = Game::instance.collision_manager->checkCollision(
                 _main_game_object, "ground");

    if( ground_obj && dy >= 0 ) {
        if( dy > 0 ) {
            _main_game_object->main_positionY = ground_obj->main_positionY -
            _main_game_object->main_height;
        }

        return true;
    }

    return false;

}


/**
    This method is responsible for damage monster in the game for 
*/

void MonsterAI::damage() {

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
        if( Game::instance.timer->getTicks() > time_damage ) {
            life--;
            time_damage = Game::instance.timer->getTicks() + 1000;
        }
        if( life <= 0 ) {
            _main_game_object->setState(GameObject::State::disabled);
            life = 3;

            // Game::instance.change_scene("Win Scene");

        }
    }
    else {
        has_damage = false;
    }

}

void MonsterAI::bullet_damage() {}

MonsterAI::~MonsterAI() {}
