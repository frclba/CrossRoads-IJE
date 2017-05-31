#include"monsterAI.hpp"
#include"game.hpp"
#include<stdio.h>
#include<stdlib.h>

MonsterAI::~MonsterAI(){}

unsigned int timestep;


bool MonsterAI::init(){
     _main_game_object->main_positionY = ground - _main_game_object->main_height;
     return true;
}

void MonsterAI::update(){

    if(Game::instance.timer->getTicks() > timestep){
    timestep =  Game::instance.timer->getTicks() + 1000;
    monster_move = 3;
    }

    m_monster_controler->play_animation("monster_walk");
    gravityF();

    if(!has_damage && m_player->main_positionX > _main_game_object->main_positionX){
      side = RIGHT;
      m_monster_controler->flipping(side);
        _main_game_object->main_positionX += monster_move;
    }if(!has_damage && m_player->main_positionX < _main_game_object->main_positionX){
      side = LEFT;
         m_monster_controler->flipping(side);
        _main_game_object->main_positionX -= monster_move;
    }else{

    }

    //monster jump
    if(_main_game_object->main_positionY > m_player->main_positionY + 30){
    //dy += jumpF;
    }


    damage();
    processPos();
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
    if(Game::instance.collision_manager->checkCollision(_main_game_object,"attack_box")){
      m_monster_controler->play_animation("monster_damage");
      has_damage = true;
      if(side == RIGHT){
	//_main_game_object->main_positionX -= 10;
      }
      if(side == LEFT){
	//_main_game_object->main_positionX += 10;
      }
    }
    else{
      has_damage = false;
    }
}
