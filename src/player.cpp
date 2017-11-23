/**
    \file player.cpp
    This file define methods content of the Player class
*/

#include "player.hpp"
#include <assert.h>

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


const int EXCEED_LIMIT_MAP = -7;
const int EMPTY_STRING = -2;
const int SUCCESS = 1;

void valid_play_animation(int code, std::string method);

/**
    Initializes the player, defining their main attributes with inicial
    values
    \return Returns the initialization confirm
*/
bool Player::init() {

    assert(_main_game_object != NULL);
    assert(image_background != NULL);

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

    valid_play_animation(animation_controller->play_animation("player_idle"),
                                                              "Player::update");

    apply_gravity();
    detect_jump();

    update_move();
    update_attack();

    detect_damage();

    /**
        \note this line enters a function that will check if the player is dead
        \note after the application of damage and before processing his position
    */
    is_dead();

    if(process_position() == EXCEED_LIMIT_MAP){
        Log::instance.error("player has crossed the border of the map");
        if(get_vertical_position() > MAXIMUM_COORDINATION_Y){
            vertical_position = MAXIMUM_COORDINATION_Y;
        }else if(get_vertical_position() < -JUMP_SIZE){
            vertical_position = -JUMP_SIZE;
        }
    }

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

    /**
        \note check if the button is up and down is necessary to change the
        \note movement based on 2 strands, based on the verification time.
    */
    if( Game::instance.keyboard->isKeyDown("space") ){
        if(get_is_attacking_ranged() == true){
            Log::instance.error(" ""is_attacking_renged"" can not be true if ""Game::instance.keyboard->isKeyDown(""space"")"" is true");
            is_attacking_ranged = false;
        }
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

    assert(Game::instance.keyboard != NULL);


    /**
        \note check if the button is up and down is necessary to change the
        \note movement based on 2 strands, based on the verification time.
    */
    if( Game::instance.keyboard->isKeyDown("f") ) {

        if(get_is_attacking_meele() == true){
            Log::instance.error(" ""is_attacking_meele"" can not be true if ""Game::instance.keyboard->isKeyDown(""f"")"" is true");
            is_attacking_meele = false;
        }
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

    assert(animation_controller != NULL);
    assert(_main_game_object != NULL);
    assert(Game::instance.timer != NULL);
    assert(attack_box_dimensions != NULL);

    if( is_attacking_meele ) {
        valid_play_animation(animation_controller->play_animation("player_attack"), "Player::apply_attack_meele");

        /**
          Audio when the player is attacking melee
        */
        AudioComponent* player_attack_audio =
                      (dynamic_cast<AudioComponent*>(
                      _main_game_object->get_component(
                      "player_attack_audio")));
        assert(player_attack_audio != NULL);

        player_attack_audio->play(0, -1);

      /**
          \note get the delay attack time, if exceeds
          \note the current time, will not apply the attack
      */
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

    if( get_is_attacking_ranged() ) {

      valid_play_animation(animation_controller->play_animation("player_attack"), "Player::apply_attack_ranged");

      /**
          Audio when the player is attacking renged
      */
      AudioComponent* player_arrow_sound =
                      (dynamic_cast<AudioComponent*>(
                      _main_game_object->get_component(
                      "player_arrow_sound")));
      assert(player_arrow_sound != NULL);

      valid_play_animation(animation_controller->play_animation("player_ranged"), "Player::apply_attack_ranged");

      player_arrow_sound->play(0, -1);
    }
    else {
        // do nothing
    }

}

void Player::detect_boby_side() {

    assert(_main_game_object != NULL);
    assert(attack_box_dimensions != NULL);

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

    /**
        \note check if the button is up and down is necessary to change the
        \note movement based on 2 strands, based on the verification time.
    */
    if( Game::instance.keyboard->isKeyDown("d") ) {
        if(get_is_walking_left() == true){
            Log::instance.error(" ""is_walking_left"" can not be true if ""Game::instance.keyboard->isKeyDown(""d"")"" is true");
            is_walking_left = false;
        }
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

}

void Player::detect_move_left() {

    assert(Game::instance.keyboard != NULL);

    /**
        \note check if the button is up and down is necessary to change the
        \note movement based on 2 strands, based on the verification time.
    */
    if( Game::instance.keyboard->isKeyDown("a") ) {
        if(get_is_walking_right() == true){
            Log::instance.error(" ""is_walking_right"" can not be true if ""Game::instance.keyboard->isKeyDown(""d"")"" is true");
            is_walking_right = false;
        }
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

}

void Player::apply_move_right() {

    assert(_main_game_object != NULL);
    assert(animation_controller != NULL);

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

        valid_play_animation(animation_controller->play_animation("player_running"), "Player::apply_move_right");
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


    /**
        \note Check if the player is at the end of the map and is able to move
        \note forward in the phase, realising the rest of the map.
    */
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

    if( is_walking_left
        && ( _main_game_object->main_positionX ) >= MINIMUM_COORDINATION_X ) {

       /**
           Audio when the player is running left
       */
       AudioComponent* player_running_audio2 =
                       (dynamic_cast<AudioComponent*>(
                       _main_game_object->get_component(
                       "player_running_audio2")));
       assert(player_running_audio2 != NULL);

       is_walking_left = true;

       valid_play_animation(animation_controller->play_animation("player_running"), "Player::apply_move_left");

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

    if( Game::instance.keyboard->isKeyDown("w")
        && ( vertical_position == MINIMUM_COORDINATION_Y ) ) {
        player_jump_audio->play(0, -1);

        /**
            \note jump size decreases vertical_position due to the fact that
            |note y coordinate increases up to down
        */
        vertical_position -= JUMP_SIZE;
    }
    else {
        // Do nothing
    }

}

int Player::process_position() {

    assert(_main_game_object != NULL);

    if(get_vertical_position() >= -JUMP_SIZE
       && vertical_position <= MAXIMUM_COORDINATION_Y){

        /**
            \note get the sum of the player's movement relative to the jump and
            \note the fall size, and determines his vertical position on the map.
        */
        _main_game_object->main_positionY += vertical_position;

        return SUCCESS;
    }else{
        return EXCEED_LIMIT_MAP;
    }

}

/**
    Apply the gravity on the player, depending where he is
    (platform or in the air)
*/
void Player::apply_gravity() {


    /**
        \note while the player is in the air, without colliding with something,
        \note will be applied +1 continuously on his vertical_position.
    */
    if( !has_ground() ) { // If the player is not on the platform

      /**
          \note gravity increases vertical_position due to the fact that
          |note y coordinate increases up to down
      */
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
    GameObject* get_ground_collision = Game::instance.collision_manager->
                                       checkCollision(_main_game_object,
                                                      "ground");

    /**
        \note Verify if player and monsters are in the ground or if they
            jumped.
    */
    if( get_ground_collision && vertical_position >= MINIMUM_COORDINATION_Y ) {

        if( vertical_position > 5 ) {
            _main_game_object->main_positionY = get_ground_collision->
                                                main_positionY -
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

    valid_life_points();

    /**
        \note get the delay damage time, if exceeds
        \note the current time, will not apply the damage
    */
    if( Game::instance.timer->getTicks() > damage_time ) {
        assert(life_points >= 1);
        life_points--;
        /**
            \note this line damage_time sum the delay damage plus the current
            \note time to avoid incorrect applied damage
        */
        damage_time = Game::instance.timer->getTicks() + DAMAGE_DELAY;
    }
    else {
        // Do nothing
    }

}

void Player::detect_low_life() {

    assert(_main_game_object != NULL);

    valid_life_points();

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

    /**
        \note the condition of this line is pertaining to rule,
        \note when a player is attacking he can not receive damage
    */
    if( !is_attacking_meele ) {

        if( (
            Game::instance.collision_manager->checkCollision(_main_game_object,
                                                             "monster") ||
            Game::instance.collision_manager->checkCollision(_main_game_object,
                                                             "fireball") ||
            Game::instance.collision_manager->checkCollision(_main_game_object,
                                                             "boss") ) ) {
             apply_damage();

             /**
                 \note this line enters a function that will check if the player
                 \note is 40% of its life to apply the referring audio
             */
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

    valid_life_points();

    /**
         \note When player is dead change for game over scene and restore points
            of life for the next game.
    */
    if( get_life_points() <= EMPTY_LIFE ){
        life_points = FULL_LIFE;
        Game::instance.change_scene("Lose Scene");
        printf("Player dead\n");
        Log::instance.info("Player dead");
    }
    else {
        // Do nothing
    }

}

void valid_play_animation(int code, std::string method) {

  if(code == EMPTY_STRING){
      Log::instance.error("Fail to play animation ... parameter ""name"" is empty , method:" + method);
      return;
  }else if(code == SUCCESS){
      Log::instance.info("Success in play animation");
  }

}

void Player::valid_life_points(){

  if(get_life_points() < 0){
      Log::instance.error("Player's life point is negative");
      life_points = EMPTY_LIFE;
      return;
  }

}

int Player::get_life_points() {

    return life_points;

}

bool Player::get_is_attacking_ranged() {

    return is_attacking_ranged;

}

bool Player::get_is_attacking_meele() {

    return is_attacking_meele;

}

bool Player::get_direction_boby_side() {

    return direction_boby_side;

}

int Player::get_vertical_position() {

    return vertical_position;

}

bool Player::get_is_walking_right() {

    return is_walking_right;

}

bool Player::get_is_walking_left() {

    return is_walking_left;

}

Player::~Player() {

}
