/**
    \file player.cpp
    This file define methods content of the Player class
*/

#include "player.hpp"

/**
    Auxiliary variable referring to the time a
    player is taking damage, if he exceeds the current time,
    he will not take the damage
 */
unsigned int damage_time = 0;

int max_height = 200;

float DAMAGE_DELAY = 1000;

/**
    Auxiliary counter for player gravity
*/
float gravity = 1;

float jump_size = 20;
float move_size = 7;

float previous_position_y = 0;

/**
    Initializes the player, defining their main attributes with inicial
    values
    \return Returns the initialization confirm
*/
bool Player::init() {

    _main_game_object->main_positionY = 502;
    _main_game_object->main_positionX = 0;

    image_background->imagePart->x = 0;

    life_points = 5;
    time_attack = 0;

    return true;

}

/**
    Call methods that update player characteristics, changing values of their
    attributes, thats make the player can move, jump, take damage, fall etc
*/
void Player::update() {

    animation_controller->play_animation("player_idle");

    apply_gravity();
    detect_jump();
    detect_move();
    update_attack();
    detect_damage();
    process_position();

}

void Player::update_attack(){

    detect_boby_side();
    detect_attack_meele();
    detect_attack_ranged();
    apply_attack_meele();
    apply_attack_ranged();

}

/**
    Detect player attack meele, in cases of direction boby side(left or right) and
    interface(buttons and their interactions). The attacks being meele or ranged
*/
void Player::detect_attack_meele() {

    if( Game::instance.keyboard->isKeyDown("space") ){
        is_attacking_meele = true;
    }
    else {
        // Do nothing
    }

    if( !Game::instance.keyboard->isKeyUp("space") ) {
        // Do nothing
    }
    else {
        is_attacking_meele = false;
    }

}

/**
    Detect player attack ranged, in cases of direction boby side(left or right) and
    interface(buttons and their interactions). The attacks being meele or ranged
*/
void Player::detect_attack_ranged() {

    if( Game::instance.keyboard->isKeyDown("f") ) {
        is_attacking_ranged = true;
    }
    else {
        // Do nothing
    }

    if( !Game::instance.keyboard->isKeyUp("f") ) {
        // Do nothing
    }
    else {
        is_attacking_ranged = false;
    }

}

void Player::apply_attack_meele() {

    if( is_attacking_meele ) {
        animation_controller->play_animation("player_attack");
        /**
          Audio when the player is attacking melee
        */
        AudioComponent* player_attack_audio =
                      (dynamic_cast<AudioComponent*>(
                      _main_game_object->get_component(
                      "player_attack_audio")));

        player_attack_audio->play(0, -1);
      if( time_attack < Game::instance.timer->getTicks() ) {
          attack_box_dimensions->setState(GameObject::State::enabled);
          time_attack = Game::instance.timer->getTicks() + 50;
      }
      else {
          attack_box_dimensions->setState(GameObject::State::disabled);
      }
    }
    else {
        // do nothing
    }

}

void Player::apply_attack_ranged() {

    if( is_attacking_ranged ) {
      animation_controller->play_animation("player_attack");

      /**
          Audio when the player is attacking renged
      */
      AudioComponent* player_arrow_sound =
                      (dynamic_cast<AudioComponent*>(
                      _main_game_object->get_component(
                      "player_arrow_sound")));

      animation_controller->play_animation("player_ranged");
      player_arrow_sound->play(0, -1);
    }
    else {
        // do nothing
    }

}

void Player::detect_boby_side() {

    if( direction_boby_side == RIGHT ) {
        attack_box_dimensions->main_positionX = _main_game_object->main_positionX +
                                       _main_game_object->main_width;
        attack_box_dimensions->main_positionY = _main_game_object->main_positionY;

        attack_box_dimensions->main_width = _main_game_object->main_width / 2;
        attack_box_dimensions->main_height = _main_game_object->main_height;
    }
    else {
        attack_box_dimensions->main_positionX = _main_game_object->main_positionX;
        attack_box_dimensions->main_positionY = _main_game_object->main_positionY;

        attack_box_dimensions->main_width = _main_game_object->main_width / 2;
        attack_box_dimensions->main_height = _main_game_object->main_height;
    }

}

/**
    Define player drive, detecting right and left movement, making interface
    interactions of his walk
*/
void Player::detect_move() {

    // Detect move right

    if( Game::instance.keyboard->isKeyDown("d") ) {
        is_walking_right = true;
    }
    else {
        // Do nothing
    }

    if( !Game::instance.keyboard->isKeyUp("d") ) {
        // Do nothing
    }
    else {
        is_walking_right = false;
    }

    // Detect move left

    if( Game::instance.keyboard->isKeyDown("a") ) {
        is_walking_left = true;
    }
    else {
        // Do nothing
    }

    if( !Game::instance.keyboard->isKeyUp("a") ) {
        // Do nothing
    }
    else {
        is_walking_left = false;
    }

    if( is_walking_right && ( _main_game_object->main_positionX +
                   _main_game_object->main_width) < 800 ) {

        /**
            Audio when the player is running right
        */
        AudioComponent* player_running_audio =
                        (dynamic_cast<AudioComponent*>(
                        _main_game_object->get_component(
                        "player_running_audio")));

        is_walking_right = true;

        animation_controller->play_animation("player_running");
        player_running_audio->play(0, -1);

        direction_boby_side = RIGHT;

        animation_controller->flipping(direction_boby_side);

        _main_game_object->main_positionX += move_size;
     }
     else if( is_walking_left && ( _main_game_object->main_positionX ) >= 0 ) {

        /**
            Audio when the player is running left
        */
        AudioComponent* player_running_audio2 =
                        (dynamic_cast<AudioComponent*>(
                        _main_game_object->get_component(
                        "player_running_audio2")));

        is_walking_right = false;

        animation_controller->play_animation("player_running");
        player_running_audio2->play(0, -1);

        direction_boby_side = LEFT;

        animation_controller->flipping(direction_boby_side);

        _main_game_object->main_positionX -= move_size;
     }
     else {
        // Do nothing
     }

    if( _main_game_object->main_positionX > 200 &&
        is_walking_right &&
        image_background->enable_camera ) {
        _main_game_object->main_positionX -= move_size;
        image_background->move_img_rect(7);
    }
    else {
        // Do nothing
    }

}

/**
    Define and detect interaction of the player jump
*/
void Player::detect_jump() {

    /**
        Audio when the player is jumping
    */
    AudioComponent* player_jump_audio = (dynamic_cast<AudioComponent*>(
                                        _main_game_object->get_component(
                                        "player_jump_audio")));

    //Player try jump and he can

    if( Game::instance.keyboard->isKeyDown("w") && ( vertical_position == 0 ) ) {
        player_jump_audio->play(0, -1);

        is_jumping = true;
        vertical_position -= jump_size;
    }
    else {
        // Do nothing
    }

}

void Player::process_position() {

    /**
        Current velocity components.
    */
    previous_position_y = _main_game_object->main_positionY;
    _main_game_object->main_positionY += vertical_position;

}

/**
    Apply the gravity on the player, depending where he is
    (platform or in the air)
*/
void Player::apply_gravity() {

    if( !has_ground() ) { // If the player is not on the platform
        vertical_position += gravity;
    }
    else {
        vertical_position = 0;
    }

}

/**
    Detects if there is a ground where the player is
    \return true has ground
    \return false hasn't ground
*/
bool Player::has_ground() {

    get_ground_collision = Game::instance.collision_manager->checkCollision(_main_game_object,
                                                              "ground");

    if( get_ground_collision && vertical_position >= 0 ) {

        if( vertical_position > 5 ) {
            _main_game_object->main_positionY = get_ground_collision->main_positionY -
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
void Player::detect_damage() {

    if( !is_attacking_meele ) {

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

                /**
                    Audio when the player taked damage and his life is low
                */
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
