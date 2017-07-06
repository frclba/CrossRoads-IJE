#include"bossAI.hpp"



bool Boss::init(){
  timestep = 0;
  move_time = 0;
  fireball_time = 0;
  side = false;
  
}


void Boss::update(){
  m_boss_animation->play_animation("boss_idle",true);

  if(_main_game_object->main_positionX > -10 &&
     _main_game_object->main_positionX + _main_game_object->main_width < 850){
  

    if (fireball_attack){
      //fireball_controller();
    }
    else if(dash_attack){
      boss_move();
    }



    m_boss_animation->flipping(!side);
  
    if(timestep < Game::instance.timer->getTicks()){
      if(m_player->main_positionY > 300){
	dash_attack = true;
	fireball_attack = false;
      m_fireball->setState(GameObject::State::disabled);
      }
      else{
	dash_attack = false;
	fireball_attack = true;
	m_boss_animation->play_animation("boss_howl");
      m_fireball->setState(GameObject::State::enabled);
      }
      
      timestep = Game::instance.timer->getTicks() + 3000;
     }

  }
  
}
void Boss::fireball_controller(){
    m_boss_animation->play_animation("boss_howl");
    if(fireball_time <  Game::instance.timer->getTicks()){
      m_fireball->setState(GameObject::State::enabled);
    }
    else{
      
    }
  
}

void Boss::boss_move(){

  m_boss_animation->play_animation("boss_dash",true);

  if(move_time < Game::instance.timer->getTicks()){
    //side = !side;
    move_time = Game::instance.timer->getTicks() + 900;
  }
  
  if(side){
    m_position->m_init_posX -=10;
  }
  
  else{
    m_position->m_init_posX +=10;
  }

  if(_main_game_object->main_positionX <=10 && side){
      side = !side;
      dash_attack = false;
  }
  if(_main_game_object->main_positionX + _main_game_object->main_width >=800 && !side){
      side = !side;
      dash_attack = false;
  }
  
  
}

Boss::~Boss(){}
