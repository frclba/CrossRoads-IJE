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
  if(Game::instance.keyboard->isKeyDown("enter")){
	Game::instance.change_scene("Fase 1");
  }
  switch (interator) {
  case 1: {
    m_story->play_animation("story1");
    break;
  }
  case 2: {
    m_story->play_animation("story2");
    break;
  }
  case 3: {
    m_story->play_animation("story3");
    break;
  }
  case 4: {
    m_story->play_animation("story4");
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
