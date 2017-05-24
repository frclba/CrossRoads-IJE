#include "stage1_scene.hpp"
#include "components/component.hpp"

bool canJump = true;
bool jump = false;
bool isFalling = false;
bool isRight = true;

int ground = 552;
int maxHeight = 200;
float gravity = 13;
float moveForce = 7;

void Stage1Scene::setup(){
  player = &get_game_object("player");

  idle = (dynamic_cast<Animation *>(player->get_component("playerIdle")));
  running = (dynamic_cast<Animation *>(player->get_component("playerRunning")));
  damage = (dynamic_cast<Animation *>(player->get_component("playerDamage")));
  attackComp = (dynamic_cast<Animation *>(player->get_component("playerAttack")));

  idle->main_state = Component::State::enabled;
  running->main_state = Component::State::disabled;
  damage->main_state = Component::State::disabled;
  attackComp->main_state = Component::State::disabled;
}

// ================================================= GAME LOGIC ====================================================
void Stage1Scene::game_logic(){
  setup();

  running->flipping(isRight);
  idle->flipping(isRight);
  attackComp->flipping(isRight);
  damage->flipping(isRight);

  jump_player(player);
  move_player(player);
  attack_player(player);
  damage_player(player);
}

// =================================================== DAMAGE LOGIC =================================================
void Stage1Scene::damage_player(GameObject* m_player){

  if((m_player->main_positionX + m_player->main_height)){
  }

  if(Game::instance.keyboard->isKeyUp(SDLK_q)){
    damageBool = false;
  }

  if(Game::instance.keyboard->isKeyDown(SDLK_q)){
    damageBool = true;
  }

  if(damageBool){
    idle->main_state = Component::State::disabled;
    running->main_state = Component::State::disabled;
    attackComp->main_state = Component::State::disabled;
    damage->main_state = Component::State::enabled;
  }
}

// ============================================= ATTACK LOGIC ===================================================
void Stage1Scene::attack_player(GameObject* m_player){

  if((m_player->main_positionX + m_player->main_height)){
  }
  if(Game::instance.keyboard->isKeyDown(SDLK_SPACE)){
    attack = true;
  }

  if(Game::instance.keyboard->isKeyUp(SDLK_SPACE)){
    attack = false;
  }

  if(attack){
    attackComp->main_state = Component::State::enabled;
    idle->main_state = Component::State::disabled;
    running->main_state = Component::State::disabled;
    damage->main_state = Component::State::disabled;
  } else{

  }
}

// ============================================== MOVE LOGIC ===================================================
void Stage1Scene::move_player(GameObject* m_player){
  //Detect move right
  if(Game::instance.keyboard->isKeyDown(SDLK_d)){
    walkR= true;
  }
  if(Game::instance.keyboard->isKeyUp(SDLK_d)){
    walkR= false;
  }

  //Detect move left
  if(Game::instance.keyboard->isKeyDown(SDLK_a)){
    walkL= true;
  }
  if(Game::instance.keyboard->isKeyUp(SDLK_a)){
    walkL= false;
  }

  if(walkR && (m_player->main_positionX + m_player->main_width) < 800){
    isRight = true;
    idle->main_state = Component::State::disabled;
    damage->main_state = Component::State::disabled;
    attackComp->main_state = Component::State::disabled;
    running->main_state = Component::State::enabled;

    m_player->main_positionX += moveForce;
  } else if(walkL && (m_player->main_positionX) >= 0){
    isRight = false;
    idle->main_state = Component::State::disabled;
    damage->main_state = Component::State::disabled;
    attackComp->main_state = Component::State::disabled;
    running->main_state = Component::State::enabled;

    m_player->main_positionX -= moveForce;
  }
}

//=========================================== JUMP LOGIC==========================================
void Stage1Scene::jump_player(GameObject* m_player){
  //Player try jump and he can jump
  if(Game::instance.keyboard->isKeyDown(SDLK_w) && canJump){
    jump = true;
  }

  if(jump){
    if(m_player->main_positionY >= (ground - maxHeight)){
      m_player->main_positionY -= gravity;
      isFalling = false;
    }else{
      jump = false;
      isFalling = true;
    }
  }

  //Test if player is not on ground
  if(isFalling){
    if((m_player->main_positionY + m_player->main_height) < ground){
      m_player->main_positionY += gravity;
      canJump = false;
    }
    else{
      canJump = true;
    }
  }
}

Stage1Scene::~Stage1Scene(){}
