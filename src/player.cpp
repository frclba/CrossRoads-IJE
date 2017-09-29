/**
    \file player.cpp
    This file define methods content of the Player class
*/

#include "player.hpp"

unsigned int damage_time = 0;

bool attacked = false;
bool canJump = true;
bool jump = false;
bool isFalling = false;
bool isRight = true;

int maxHeight = 200;

float DAMAGE_DELAY = 1000;
float gravity = 1;
float jumpF = 20;
float moveForce = 7;
float monster_move = 4;
float prev_position_y = 0;
float dy = 0;

/**
    Initializes the player, defining their main attributes with inicial
    values
    \return Returns the initialization confirm
*/
bool Player::init() {

    _main_game_object->main_positionY = 502;
    _main_game_object->main_positionX = 0;

    m_background->imagePart->x = 0;

    life_points = 5;
    time_attack = 0;

    return true;

}

/**
    Call methods that update player characteristics, changing values of their
    attributes, thats make the player can move, jump, take damage, fall etc
*/
void Player::update() {

    animCtrl->play_animation("player_idle");

    gravityF();
    jump_player();
    move_player();
    attack_player();
    damage();
    processPos();

}

/**
    Define and detect player attacks, in cases of side(left or right) and
    interface(buttons and their interactions). The attacks being meele or ranged
*/
void Player::attack_player() {

    if( side == RIGHT ) {
        m_attack_box->main_positionX = _main_game_object->main_positionX +
                                       _main_game_object->main_width;
        m_attack_box->main_positionY = _main_game_object->main_positionY;

        m_attack_box->main_width = _main_game_object->main_width / 2;
        m_attack_box->main_height = _main_game_object->main_height;
    }
    else {
        m_attack_box->main_positionX = _main_game_object->main_positionX;
        m_attack_box->main_positionY = _main_game_object->main_positionY;

        m_attack_box->main_width = _main_game_object->main_width / 2;
        m_attack_box->main_height = _main_game_object->main_height;
    }


    if( Game::instance.keyboard->isKeyDown("space") ){
        attack_meele = true;
    }
    else {
        // Do nothing
    }

    if( !Game::instance.keyboard->isKeyUp("space") ) {
        // Do nothing
    }
    else {
        attack_meele = false;
    }

    if( Game::instance.keyboard->isKeyDown("f") ) {
        attack_ranged = true;
    }
    else {
        // Do nothing
    }

    if( !Game::instance.keyboard->isKeyUp("f") ) {
        // Do nothing
    }
    else {
        attack_ranged = false;
    }

    if( attack_meele || attack_ranged ) {
      animCtrl->play_animation("player_attack");
      if( attack_meele ) {
          AudioComponent* player_attack_audio =
                          (dynamic_cast<AudioComponent*>(
                          _main_game_object->get_component(
                          "player_attack_audio")));

          player_attack_audio->play(0, -1);
          if( time_attack < Game::instance.timer->getTicks() ) {
              m_attack_box->setState(GameObject::State::enabled);
              time_attack = Game::instance.timer->getTicks() + 50;
          }
          else {
              m_attack_box->setState(GameObject::State::disabled);
          }
      }
      else {
          AudioComponent* player_arrow_sound =
                          (dynamic_cast<AudioComponent*>(
                          _main_game_object->get_component(
                          "player_arrow_sound")));

          animCtrl->play_animation("player_ranged");
          player_arrow_sound->play(0, -1);
      }
    }
    else {
        // do nothing
    }

}

/**
    Define player drive, detecting right and left movement, making interface
    interactions of his walk
*/
void Player::move_player() {

    // Detect move right

    if( Game::instance.keyboard->isKeyDown("d") ) {
        walkR = true;
    }
    else {
        // Do nothing
    }

    if( !Game::instance.keyboard->isKeyUp("d") ) {
        // Do nothing
    }
    else {
        walkR = false;
    }

    // Detect move left

    if( Game::instance.keyboard->isKeyDown("a") ) {
        walkL = true;
    }
    else {
        // Do nothing
    }

    if( !Game::instance.keyboard->isKeyUp("a") ) {
        // Do nothing
    }
    else {
        walkL = false;
    }

    if( walkR && ( _main_game_object->main_positionX +
                   _main_game_object->main_width) < 800 ) {

        AudioComponent* player_running_audio =
                        (dynamic_cast<AudioComponent*>(
                        _main_game_object->get_component(
                        "player_running_audio")));

        isRight = true;

        animCtrl->play_animation("player_running");
        player_running_audio->play(0, -1);

        side = RIGHT;

        animCtrl->flipping(side);

        _main_game_object->main_positionX += moveForce;
     }
     else if( walkL && ( _main_game_object->main_positionX ) >= 0 ) {

        AudioComponent* player_running_audio2 =
                        (dynamic_cast<AudioComponent*>(
                        _main_game_object->get_component(
                        "player_running_audio2")));

        isRight = false;

        animCtrl->play_animation("player_running");
        player_running_audio2->play(0, -1);

        side = LEFT;

        animCtrl->flipping(side);

        _main_game_object->main_positionX -= moveForce;
     }
     else {
        // Do nothing
     }

    if( _main_game_object->main_positionX > 200 &&
        walkR &&
        m_background->enable_camera ) {
        _main_game_object->main_positionX -= moveForce;
        m_background->move_img_rect(7);
    }
    else {
        // Do nothing
    }

}

/**
    Define and detect interaction of the player jump
*/
void Player::jump_player() {

    AudioComponent* player_jump_audio = (dynamic_cast<AudioComponent*>(
                                        _main_game_object->get_component(
                                        "player_jump_audio")));

    //Player try jump and he can

    if( Game::instance.keyboard->isKeyDown("w") && ( dy == 0 ) ) {
        player_jump_audio->play(0, -1);

        jump = true;
        dy -= jumpF;
    }
    else {
        // Do nothing
    }

}

void Player::processPos() {

    prev_position_y = _main_game_object->main_positionY;
    _main_game_object->main_positionY += dy; // Current velocity components.

}

/**
    Apply the gravity on the player, depending where he is
    (platform or in the air)
*/
void Player::gravityF() {

    if( !has_ground() ) { // If the player is not on the platform
        dy += gravity;
    }
    else {
        dy = 0;
    }

}

/**
    Detects if there is a ground where the player is
    \return true has ground
    \return false hasn't ground
*/
bool Player::has_ground() {

    ground = Game::instance.collision_manager->checkCollision(_main_game_object,
                                                              "ground");

    if( ground && dy >= 0 ) {

        if( dy > 5 ) {
            _main_game_object->main_positionY = ground->main_positionY -
                                                _main_game_object->main_height;
        }
        else {
            // Do nothing
        }

        return true;

    }
    else {

        return false;

    }

}

/**
    Detect damage on the player and apply the changes
*/
void Player::damage() {

    if( !attack_meele ) {

        if( (
            Game::instance.collision_manager->checkCollision(_main_game_object,
                                                             "monster") ||
            Game::instance.collision_manager->checkCollision(_main_game_object,
                                                             "fireball") ||
            Game::instance.collision_manager->checkCollision(_main_game_object,
                                                             "boss") ) ) {
             if( Game::instance.timer->getTicks() > damage_time ) {
                 life_points--;
                 damage_time = Game::instance.timer->getTicks() + 1000;
             }
             else {
                 // Do nothing
             }

             if( life_points == 2 ) {
                AudioComponent* player_low_life_audio =
                                (dynamic_cast<AudioComponent*>(
                                _main_game_object->get_component(
                                "player_low_life_audio")));
                player_low_life_audio->play(0, -1);
             }
             else {
                // Do nothing
             }

             if( life_points > 0) {
                 // Do nothing
             }
             else {
                 life_points = 5;
                 Game::instance.change_scene("Lose Scene");
             }
        }
        else {
            // Do nothing
        }
    }
    else {
        // Do nothing
    }

    if( life_points > 0 ) {
        // Do nothing
    }
    else {
        life_points = 5;
        Game::instance.change_scene("Lose Scene");
    }

}

/**
    Detects if the player is dead
*/
void Player::is_dead() {

    if( life_points <= 0 ){
        printf("Player dead\n");
        Log::instance.info("Player dead");
    }
    else {
        // Do nothing
    }

}

Player::~Player() {

}
