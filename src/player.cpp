#include "player.hpp"

float DAMAGE_DELAY = 1000;
unsigned int damage_time = 0;
bool attacked = false;

bool canJump = true;
bool jump = false;
bool isFalling = false;
bool isRight = true;

int maxHeight = 200;
float gravity = 1;
float jumpF = 20;
float moveForce = 7;
float monster_move = 4;
float prev_position_y;

float dy = 0;

bool Player::init(){
    _main_game_object->main_positionY = 502;
    _main_game_object->main_positionX = 0;
    m_background->imagePart->x = 0;
    life_points = 5;
    time_attack = 0;

    return true;
}

// ================================================= GAME LOGIC ====================================================
void Player::update(){

    animCtrl->play_animation("player_idle");
    gravityF();
    jump_player();
    move_player();
    attack_player();
    damage();
    // is_dead();

    processPos();
}

// // ============================================= ATTACK LOGIC ===================================================
void Player::attack_player(){

    if(side == LEFT){
        m_attack_box->main_positionX = _main_game_object->main_positionX;
        m_attack_box->main_positionY = _main_game_object->main_positionY;
        m_attack_box->main_width = _main_game_object->main_width/2 ;
        m_attack_box->main_height = _main_game_object->main_height;
    }
    if(side == RIGHT){
        m_attack_box->main_positionX = _main_game_object->main_positionX + _main_game_object->main_width;
        m_attack_box->main_positionY = _main_game_object->main_positionY;
        m_attack_box->main_width = _main_game_object->main_width/2 ;
        m_attack_box->main_height = _main_game_object->main_height;
    }

    if(Game::instance.keyboard->isKeyDown("space")){
        attack_meele = true;
    }

    if(Game::instance.keyboard->isKeyUp("space")){
        attack_meele = false;
    }
    if(Game::instance.keyboard->isKeyDown("f")){
        attack_ranged = true;
    }

    if(Game::instance.keyboard->isKeyUp("f")){
        attack_ranged = false;
    }


    if(attack_meele||attack_ranged){
      if(attack_meele){
	animCtrl->play_animation("player_attack");
	if(time_attack < Game::instance.timer->getTicks()){
	  m_attack_box->setState(GameObject::State::enabled);
	  time_attack = Game::instance.timer->getTicks() + 50;
	}
	else{
	  m_attack_box->setState(GameObject::State::disabled);
	}
      }
      else{
	animCtrl->play_animation("player_ranged");
      }
    }else{

    }
}

// // ============================================== MOVE LOGIC ===================================================
void Player::move_player(){
    AudioComponent* player_running_audio = (dynamic_cast<AudioComponent*> (_main_game_object->get_component("player_running_audio")));
    AudioComponent* player_running_audio2 = (dynamic_cast<AudioComponent*> (_main_game_object->get_component("player_running_audio2")));

    //     //Detect move right
    if(Game::instance.keyboard->isKeyDown("d")){
        walkR= true;
    }
    if(Game::instance.keyboard->isKeyUp("d")){
        walkR= false;
    }
    //
    //Detect move left
    if(Game::instance.keyboard->isKeyDown("a")){
        walkL= true;
    }
    if(Game::instance.keyboard->isKeyUp("a")){
        walkL= false;
    }
    //
    if(walkR && (_main_game_object->main_positionX+_main_game_object->main_width)<800){
        isRight = true;
        animCtrl->play_animation("player_running");
        player_running_audio->play(0, -1);
        side = RIGHT;
        animCtrl->flipping(side);
        _main_game_object->main_positionX += moveForce;

    } else if(walkL && (_main_game_object->main_positionX)>=0 ){
        isRight = false;
        animCtrl->play_animation("player_running");
        player_running_audio2->play(0, -1);
        side = LEFT;
        animCtrl->flipping(side);
        _main_game_object->main_positionX -= moveForce;
    }

    if(_main_game_object->main_positionX > 200 && walkR && m_background->enable_camera){
      _main_game_object->main_positionX -= moveForce;
      m_background->move_img_rect(7);
    }
}

// //=========================================== JUMP LOGIC==========================================
void Player::jump_player(){
    //Player try jump and he can jump
    if(Game::instance.keyboard->isKeyDown("w") && (dy==0)){
        jump = true;
        dy -= jumpF;
    }
}

void Player::processPos(){
    prev_position_y = _main_game_object->main_positionY;
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
    ground = Game::instance.collision_manager->checkCollision(_main_game_object,"ground");
    if(ground && dy>=0 ){
        if(dy>5){
            _main_game_object->main_positionY = ground->main_positionY - _main_game_object->main_height ;
        }
        return true;
    }
    return false;

}

void Player::damage(){
  if(!attack_meele && (Game::instance.collision_manager->checkCollision(_main_game_object,"monster")||
		       Game::instance.collision_manager->checkCollision(_main_game_object,"fireball")||
		       Game::instance.collision_manager->checkCollision(_main_game_object,"boss"))){
        animCtrl->play_animation("player_damage");
        if(Game::instance.timer->getTicks() > damage_time){
            life_points--;
            damage_time = Game::instance.timer->getTicks() + 1000;
        }
        if(life_points <= 0){
	  //_main_game_object->setState(GameObject::State::disabled);
	    life_points = 5;
	    Game::instance.change_scene("Lose Scene");
        }
    }
}

void Player::is_dead(){
    if(life_points <= 0){
        printf("Player dead\n");
        Log::instance.info("Player dead");
    }
}

Player::~Player(){}
