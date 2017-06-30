#include"monsterAI.hpp"
#include"game.hpp"
#include<stdio.h>
#include<stdlib.h>

unsigned int time_damage;
const int PLAYER_DISTANCE = 250;
const int PLAYER_ATTACK_DISTANCE = 150;



bool MonsterAI::init(){
     _main_game_object->main_positionY = ground - _main_game_object->main_height;
     _main_game_object->main_positionX = 400;
     return true;
}

void MonsterAI::update(){
    m_monster_controler->play_animation("monster_walk");
    gravityF();

    move_monster();
    damage();
    processPos();
    jump_monster();


    if(_main_game_object->main_positionX<0||_main_game_object->main_positionX+_main_game_object->main_width>800){
      _main_game_object->setState(GameObject::State::disabled);
    }

}

bool MonsterAI::see_player(){
    if(fabs(_main_game_object->main_positionX - m_player->main_positionX) <= PLAYER_DISTANCE){
        return true;
    }else{
        return false;
    }
}

void MonsterAI::jump_monster(){
    //monster jump
    bool isOnGround = Game::instance.collision_manager->checkCollision(m_player,"ground");

    if(see_player() && isOnGround && _main_game_object->main_positionY > m_player->main_positionY){
        dy += jumpF;
    }
}

void MonsterAI::move_monster(){
    bool isSee = see_player();
  if(isSee && !has_damage && m_player->main_positionX > _main_game_object->main_positionX){
    m_monster_controler->flipping(true);
    _main_game_object->main_positionX += MONSTER_MOVE;
}if(isSee && !has_damage && m_player->main_positionX < _main_game_object->main_positionX){
    m_monster_controler->flipping(false);
    _main_game_object->main_positionX -= MONSTER_MOVE;
  }else{
  }
}

void MonsterAI::processPos(){
  //std::cout<<dy<<std::endl;
   _main_game_object->main_positionY -= dy;   // current velocity components.
}

void MonsterAI::gravityF(){
  if(_main_game_object->main_positionY > (ground - _main_game_object->main_height)){
     _main_game_object->main_positionY = ground - _main_game_object->main_height;
  }
  if ( (_main_game_object->main_positionY + _main_game_object->main_height) < ground ){
         dy -= gravity;
  }

  else{
    //     dy = 0;
  }
}


void MonsterAI::damage(){
    bullet = Game::instance.collision_manager->checkCollision(_main_game_object,"bullet");
    if(Game::instance.collision_manager->checkCollision(_main_game_object,"attack_box")||bullet){
      m_monster_controler->play_animation("monster_damage");
      if(bullet){
        bullet->setState(GameObject::State::disabled);
      }
      has_damage = true;
      if(side == RIGHT){
	//_main_game_object->main_positionX -= 10;
      }
      if(side == LEFT){
	//_main_game_object->main_positionX += 10;
      }
      if(Game::instance.timer->getTicks() > time_damage){
	life--;
	time_damage = Game::instance.timer->getTicks() + 1000;
      }
      if(life <= 0){
	    _main_game_object->setState(GameObject::State::disabled);
	    //Game::instance.change_scene("Win Scene");
      }
    }
    else{
      has_damage = false;
    }
}

void MonsterAI::bullet_damage(){


}

MonsterAI::~MonsterAI(){}
