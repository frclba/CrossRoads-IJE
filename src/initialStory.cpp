/**
    \file initialStory.cpp
    This file implements the initialStory class
*/
#include "initialStory.hpp"

InitialStory::~InitialStory(){}



/**
    This method initiates the class InitialStory
    initiates que interation in 0.
*/

bool InitialStory::init() {
    interator = 0;
}

/**
    This method is responsible for updating in the game for story initial

*/
void InitialStory::update() {

  m_story->flipping( false );

  if( timestep < Game::instance.timer->getTicks() ) {
      interator = interator + 1;
      timestep = Game::instance.timer->getTicks() + 500*6;
  }
  else {
      // Do nothing
  }

  if( Game::instance.keyboard->isKeyDown( "enter" ) ) {
	    Game::instance.change_scene("Fase 1");
  }
  else {
      // Do nothing
  }

  switch ( interator ) {
      case 1: {
          m_story->play_animation( "story1" );
          break;
      }
      case 2: {
          m_story->play_animation( "story2" );
          break;
      }
      case 3: {
          m_story->play_animation( "story3" );
          break;
      }
      case 4: {
          m_story->play_animation( "story4" );
          break;
      }
      case 5: {
          Game::instance.change_scene( "Fase 1" );
          break;
      }
      default:
          break;
      }

}
