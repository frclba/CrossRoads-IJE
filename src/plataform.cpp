#include "plataform.hpp"

Plataform::~Plataform(){}


bool Plataform::init(){
  _main_game_object->main_positionX = m_init_posX;
  _main_game_object->main_positionY = m_init_posY;
  return true;
}


void Plataform::update(){
  _main_game_object->main_positionY = m_init_posY;
  _main_game_object->main_positionX = m_init_posX - m_background->imagePart->x;
}
