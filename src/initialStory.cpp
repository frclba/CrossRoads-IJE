#include"initialStory.hpp"

InitialStory::~InitialStory(){}

bool InitialStory::init(){
  interator = 0;
}

void InitialStory::update(){
  m_story->flipping(false);
  if(timestep < Game::instance.timer->getTicks()){
    interator = interator + 1;
    timestep = Game::instance.timer->getTicks() + 500*6;
  }
  switch (interator) {
  case 1: {
    m_image1->setState(GameObject::State::enabled); 
    m_image2->setState(GameObject::State::disabled);
    break;
  }
  case 2: {
    m_story->play_animation("story2");
    m_image1->setState(GameObject::State::disabled); 
    m_image2->setState(GameObject::State::disabled); 
    break;
  }
  case 3: {
    m_image1->setState(GameObject::State::disabled); 
    m_image2->setState(GameObject::State::enabled);
    break;
  }
  case 4: {
    m_story->play_animation("story4");
    m_image1->setState(GameObject::State::disabled); 
    m_image2->setState(GameObject::State::disabled);
    break;
  }
  case 5: {
    Game::instance.change_scene("Fase 1");
    break;
  }
  default:
    break;
  }
}
