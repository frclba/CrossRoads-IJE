#include "player.hpp"

bool canJump = true;
bool jump = false;
bool isFalling = false;
bool isRight = true;

int ground = 552;
int maxHeight = 200;
float gravity = 1;
float jumpF = 20;
float moveForce = 7;
float monster_move = 4;

float dy = 0;

bool Player::init(){return true;}

// ================================================= GAME LOGIC ====================================================
void Player::update(){

  animCtrl->play_animation("player_idle");
    gravityF();
    jump_player();
    move_player();
    attack_player();

    processPos();
}

// // ============================================= ATTACK LOGIC ===================================================
void Player::attack_player(){

    if(Game::instance.keyboard->isKeyDown(SDLK_SPACE)){
        attack = true;
    }

    if(Game::instance.keyboard->isKeyUp(SDLK_SPACE)){
        attack = false;
    }

    if(attack){
        animCtrl->play_animation("player_attack");
    }else{

    }
}

// // ============================================== MOVE LOGIC ===================================================
void Player::move_player(){
//     //Detect move right
    if(Game::instance.keyboard->isKeyDown(SDLK_d)){
        walkR= true;
    }
    if(Game::instance.keyboard->isKeyUp(SDLK_d)){
        walkR= false;
    }
//
    //Detect move left
    if(Game::instance.keyboard->isKeyDown(SDLK_a)){
        walkL= true;
    }
    if(Game::instance.keyboard->isKeyUp(SDLK_a)){
        walkL= false;
    }
//
    if(walkR && (_main_game_object->main_positionX+_main_game_object->main_width)<800){
        isRight = true;
	animCtrl->play_animation("player_running");
        animCtrl->flipping(true);
	_main_game_object->main_positionX += moveForce;

    } else if(walkL && (_main_game_object->main_positionX)>=0 ){
        isRight = false;
        animCtrl->play_animation("player_running");
        animCtrl->flipping(false);
        _main_game_object->main_positionX -= moveForce;
    }
}

// //=========================================== JUMP LOGIC==========================================
void Player::jump_player(){
    //Player try jump and he can jump
  if(Game::instance.keyboard->isKeyDown(SDLK_w) && (dy==0)){
	dy -= jumpF;
    }
}

void Player::processPos()
{
     _main_game_object->main_positionY += dy;   // current velocity components.
}


void Player::gravityF(){
  if (!has_ground()){      // If the player is not on the platform
    dy += gravity;
  }

  else{
    dy = 0;
  }
}
bool Player::has_ground(){
  if(_main_game_object->main_positionY + dy + _main_game_object->main_height > ground){
    return true;
  }
  return false;
  
}

Player::~Player(){}
