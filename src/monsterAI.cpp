#include"monsterAI.hpp"
#include"game.hpp"
#include<stdio.h>
#include<stdlib.h>

unsigned int timestep;

bool MonsterAI::init(){
     _main_game_object->main_positionY = ground - _main_game_object->main_height;
     return true;
}

void MonsterAI::update(){

    m_monster_controler->play_animation("monster_walk");
    gravityF();

    move_monster();
    jump_monster();
    processPos();
}

void MonsterAI::jump_monster(){
    //monster jump
    if(_main_game_object->main_positionY > m_player->main_positionY + 30){
        //dy += jumpF;
    }
}

void MonsterAI::move_monster(){
    if(m_player->main_positionX > _main_game_object->main_positionX){
        m_monster_controler->flipping(true);
        _main_game_object->main_positionX += MONSTER_MOVE;
    }if(m_player->main_positionX < _main_game_object->main_positionX){
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

MonsterAI::~MonsterAI(){}
