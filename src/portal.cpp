#include <portal.hpp>

Portal::~Portal(){}

bool Portal::init(){
  _main_game_object->main_positionX = 700;
  _main_game_object->main_positionY = 500;
  interator = 0;
  timestep = 0;
  monster_number = 0;

  return true;
}

void Portal::update(){

  if(timestep < Game::instance.timer->getTicks() && m_monsters[interator]->state() == GameObject::State::disabled){
    m_monsters[interator]->main_positionX = _main_game_object->main_positionX;
    m_monsters[interator]->main_positionY = _main_game_object->main_positionY;
    m_monsters[interator]->setState(GameObject::State::enabled);
    interator = (interator + 1)%m_monsters.size();

    monster_number++;
    timestep = Game::instance.timer->getTicks() + 1000;
  }

    m_background->enable_camera = true;
  if(monster_number > 10 && m_background->imagePart->x == 0){
    m_background->enable_camera = true;
    _main_game_object->setState(GameObject::State::disabled);

  }
  
}














//so chamar na main
void Portal::add_monster(GameObject* monster){
  monster->setState(GameObject::State::disabled);
  m_monsters.push_back(monster);
}
