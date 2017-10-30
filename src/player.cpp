/**
    \file player.cpp
    This file define methods content of the Player class
*/

#include "player.hpp"
#include <assert.h>
 
/// \note Declares player constants.  
const int MAXIMUM_SCREEN_WIDTH = 200;

/**
    Auxiliary counter for player gravity
*/
const float GRAVITY = 1;

const float JUMP_SIZE = 20;
const float MOVE_SIZE = 7;

const int FULL_LIFE = 5;
const int FORTY_PERCENT_LIFE = 2;
const int EMPTY_LIFE = 0;

const int MAXIMUM_COORDINATION_Y = 502;
const int MINIMUM_COORDINATION_Y = 0;

const int MAXIMUM_COORDINATION_X = 800;
const int MINIMUM_COORDINATION_X = 0;

const int MINIMUM_ATTACK_TIME = 0;

const int ATTACK_DELAY = 50;
const int DAMAGE_DELAY = 1000;

/**
    Initializes the player, defining their main attributes with inicial
    values
    \return Returns the initialization confirm
*/
bool Player::init() {

    assert(_main_game_object != NULL);
    assert(image_background != NULL);

    /// \note Initialize player initial position and status.
    _main_game_object->main_positionY = MAXIMUM_COORDINATION_Y;
    _main_game_object->main_positionX = MINIMUM_COORDINATION_X;

    image_background->image_measures->x = 0;

    life_points = FULL_LIFE;
    time_attack = MINIMUM_ATTACK_TIME;

    return true;

}

/**
    Call methods that update player characteristics, changing values of their
    attributes, thats make the player can move, jump, take damage, fall etc
*/
void Player::update() {

    assert(animation_controller != NULL);

    /// \note Update player status, position, and actions. 
    animation_controller->play_animation("player_idle");

    apply_gravity();
    detect_jump();

    update_move();
    update_attack();

    detect_damage();
    is_dead();
    process_position();

}

void Player::update_attack() {
    
    /**
        \note Update player body side and type of attack detection and
            activation.
    */
    detect_boby_side();
    detect_attack_meele();
    detect_attack_ranged();

    apply_attack_meele();
    apply_attack_ranged();

}

void Player::update_move() {

    /**
        \note Update player movement to the left ou right detection and
            activation.
    */
    detect_move_right();
    detect_move_left();

    apply_move_right();
    detect_background();
    apply_move_left();

}

/**
    Detect player attack meele, in cases of direction boby side(left or right) and
    interface(buttons and their interactions). The attacks being meele or ranged
*/
void Player::detect_attack_meele() {

    assert(Game::instance.keyboard != NULL);

    /// \note Detect if player attack is meele. 
    if( Game::instance.keyboard->isKeyDown("space") ){
        is_attacking_meele = true;
    }
    else {
        // Do nothing
    }

    /// \note Detect if player attack isn't meele. 
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

    assert(Game::instance.keyboard != NULL);

    /// \note Detect if player attack is ranged. 
    if( Game::instance.keyboard->isKeyDown("f") ) {
        is_attacking_ranged = true;
    }
    else {
        // Do nothing
    }

    /// \note Detect if player attack isn't ranged.
    if( !Game::instance.keyboard->isKeyUp("f") ) {
        // Do nothing
    }
    else {
        is_attacking_ranged = false;
    }

}

void Player::apply_attack_meele() {

    assert(animation_controller != NULL);
    assert(_main_game_object != NULL);
    assert(Game::instance.timer != NULL);
    assert(attack_box_dimensions != NULL);

    /// \note Apply audio of meele attack of the player.  
    if( is_attacking_meele ) {
        animation_controller->play_animation("player_attack");
        /**
          Audio when the player is attacking melee
        */
        AudioComponent* player_attack_audio =
                      (dynamic_cast<AudioComponent*>(
                      _main_game_object->get_component(
                      "player_attack_audio")));
        assert(player_attack_audio != NULL);

        player_attack_audio->play(0, -1);
      /// \note Apply delay and position of meele attack of the player.
      if( time_attack < Game::instance.timer->getTicks() ) {
          attack_box_dimensions->setState(GameObject::State::enabled);
          time_attack = Game::instance.timer->getTicks() + ATTACK_DELAY;
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

    assert(animation_controller != NULL);
    assert(_main_game_object != NULL);

    /// \note Apply audio of ranged attack of the player.
    if( get_is_attacking_ranged() ) {
      animation_controller->play_animation("player_attack");

      /**
          Audio when the player is attacking renged
      */
      AudioComponent* player_arrow_sound =
                      (dynamic_cast<AudioComponent*>(
                      _main_game_object->get_component(
                      "player_arrow_sound")));
      assert(player_arrow_sound != NULL);

      animation_controller->play_animation("player_ranged");
      player_arrow_sound->play(0, -1);
    }
    else {
        // do nothing
    }

}

void Player::detect_boby_side() {

    assert(_main_game_object != NULL);
    assert(attack_box_dimensions != NULL);

    /// \note Detect if player body direction is right or left.
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
void Player::detect_move_right() {

    assert(Game::instance.keyboard != NULL);

    /// \note Detect if player move is right.
    if( Game::instance.keyboard->isKeyDown("d") ) {
        is_walking_right = true;
    }
    else {
        // Do nothing
    }

    /// \note Detect if player move isn't right.
    if( !Game::instance.keyboard->isKeyUp("d") ) {
        // Do nothing
    }
    else {
        is_walking_right = false;
    }

}

void Player::detect_move_left() {

    assert(Game::instance.keyboard != NULL);

    /// \note Detect if player move is left.
    if( Game::instance.keyboard->isKeyDown("a") ) {
        is_walking_left = true;
    }
    else {
        // Do nothing
    }

    /// \note Detect if player move isn't left.
    if( !Game::instance.keyboard->isKeyUp("a") ) {
        // Do nothing
    }
    else {
        is_walking_left = false;
    }

}

void Player::apply_move_right() {

    assert(_main_game_object != NULL);
    assert(animation_controller != NULL);

    /// \note Apply direction to the right and running audio of the player.
    if( is_walking_right && ( _main_game_object->main_positionX +
                   _main_game_object->main_width) < MAXIMUM_COORDINATION_X ) {

        /**
            Audio when the player is running right
        */
        AudioComponent* player_running_audio =
                        (dynamic_cast<AudioComponent*>(
                        _main_game_object->get_component(
                        "player_running_audio")));
        assert(player_running_audio != NULL);

        is_walking_right = true;

        animation_controller->play_animation("player_running");
        player_running_audio->play(0, -1);

        direction_boby_side = RIGHT;

        animation_controller->flipping(direction_boby_side);

        _main_game_object->main_positionX += MOVE_SIZE;
     }
     else {
        // Do nothing
     }

}

void Player::detect_background() {

    assert(_main_game_object != NULL);
    assert(image_background != NULL);

    /// \note Detect background when player is walking to the right.
    if( _main_game_object->main_positionX > MAXIMUM_SCREEN_WIDTH &&
        is_walking_right &&
        image_background->enable_camera ) {
        _main_game_object->main_positionX -= MOVE_SIZE;
        image_background->move_img_rect(7);
    }
    else {
        // Do nothing
    }

}

void Player::apply_move_left() {

    assert(_main_game_object != NULL);
    assert(animation_controller != NULL);

    /// \note Apply direction to the left and running audio of the player.
    if( is_walking_left && ( _main_game_object->main_positionX ) >= MINIMUM_COORDINATION_X ) {

       /**
           Audio when the player is running left
       */
       AudioComponent* player_running_audio2 =
                       (dynamic_cast<AudioComponent*>(
                       _main_game_object->get_component(
                       "player_running_audio2")));
       assert(player_running_audio2 != NULL);

       is_walking_left = true;

       animation_controller->play_animation("player_running");
       player_running_audio2->play(0, -1);

       direction_boby_side = LEFT;

       animation_controller->flipping(direction_boby_side);

       _main_game_object->main_positionX -= MOVE_SIZE;
    }
    else {
        // Do nothing
    }

}

/**
    Define and detect interaction of the player jump
*/
void Player::detect_jump() {

    assert(_main_game_object != NULL);
    assert(Game::instance.keyboard != NULL);

    /**
        Audio when the player is jumping
    */
    AudioComponent* player_jump_audio = (dynamic_cast<AudioComponent*>(
                                        _main_game_object->get_component(
                                        "player_jump_audio")));
    assert(player_jump_audio != NULL);

    /// \note Detect if player jump and play jump audio if he jump is detected.
    if( Game::instance.keyboard->isKeyDown("w") && ( vertical_position == MINIMUM_COORDINATION_Y ) ) {
        player_jump_audio->play(0, -1);

        vertical_position -= JUMP_SIZE;
    }
    else {
        // Do nothing
    }

}

void Player::process_position() {

    assert(_main_game_object != NULL);

    _main_game_object->main_positionY += vertical_position;
    assert(vertical_position >= -JUMP_SIZE && vertical_position <= MAXIMUM_COORDINATION_Y);
}

/**
    Apply the gravity on the player, depending where he is
    (platform or in the air)
*/
void Player::apply_gravity() {

    /// \note Apply gravity when player and monsters jump.
    if( !has_ground() ) { // If the player is not on the platform
        vertical_position += GRAVITY;
    }
    else {
        vertical_position = MINIMUM_COORDINATION_Y;
        assert(vertical_position == 0);
    }

}

/**
    Detects if there is a ground where the player is
    \return true has ground
    \return false hasn't ground
*/
bool Player::has_ground() {

    assert(_main_game_object != NULL);
    assert(Game::instance.collision_manager != NULL);

    /**
        Object instance that helps to check if have terrain where the player is
    */
    GameObject* get_ground_collision = Game::instance.collision_manager->checkCollision(_main_game_object,
                                                              "ground");

    /**
        \note Verify if player and monsters are in the ground or if they
            jumped.
    */
    if( get_ground_collision && vertical_position >= MINIMUM_COORDINATION_Y ) {

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

void Player::apply_damage() {

    assert(Game::instance.timer != NULL);

    /**
        \note Apply player and monster damage with delay of damage inflicting
            in 1 point life.
    */
    if( Game::instance.timer->getTicks() > damage_time ) {
        assert(life_points >= 1);
        life_points--;
        damage_time = Game::instance.timer->getTicks() + DAMAGE_DELAY;
    }
    else {
        // Do nothing
    }

}

void Player::detect_low_life() {

    assert(_main_game_object != NULL);

    /// \note Detect and play audio when player is with low life.
    if( life_points == FORTY_PERCENT_LIFE ) {

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

}

/**
    Detect damage on the player and apply the changes
*/
void Player::detect_damage() {

    assert(_main_game_object != NULL);
    assert(Game::instance.collision_manager != NULL);

    /// \note Detect when boss, monsters or player give damage.
    if( !is_attacking_meele ) {

        if( (
            Game::instance.collision_manager->checkCollision(_main_game_object,
                                                             "monster") ||
            Game::instance.collision_manager->checkCollision(_main_game_object,
                                                             "fireball") ||
            Game::instance.collision_manager->checkCollision(_main_game_object,
                                                             "boss") ) ) {
             apply_damage();

             detect_low_life();
        }
        else {
            // Do nothing
        }
    }
    else {
        // Do nothing
    }

}

/**
    Detects if the player is dead
*/
void Player::is_dead() {

    /**
         \note When player is dead change for game over scene and restore points
            of life for the next game.
    */
    if( life_points <= EMPTY_LIFE ){
        life_points = FULL_LIFE;
        Game::instance.change_scene("Lose Scene");
        printf("Player dead\n");
        Log::instance.info("Player dead");
    }
    else {
        // Do nothing
    }

}

int Player::get_life_points() {

    return life_points;

}

bool Player::get_is_attacking_ranged() {

    return is_attacking_ranged;

}

bool Player::get_direction_boby_side() {

    return direction_boby_side;

}


Player::~Player() {

}
