/**
    \file initialStory.cpp
    This file implements the initialStory class
*/
#include "initialStory.hpp"

const int TIME_STEP_INCREASE = 500 * 6;

InitialStory::~InitialStory(){}

/**
    This method initiates the class InitialStory
    initiates que iteration in 0.
*/

bool InitialStory::init() {
    iterator = 0;
}

/**
    This method is responsible for switching between storys
*/
void switchStories(int iterator, AnimationControllerComponent *m_story) {

    switch ( iterator ) {
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

/**
    This method is responsible for starting the game by pressing the enter key
*/
void startByEnter() {
    if( Game::instance.keyboard->isKeyDown( "enter" ) ) {
  	    Game::instance.change_scene("Fase 1");
    }
    else {
        // Do nothing
    }
}

/**
    This method is responsible for updating in the game for stories initial
*/
void InitialStory::update() {

  m_story->flipping( false );

  if( time_step < Game::instance.timer->getTicks() ) {
      iterator = iterator + 1;
      time_step = Game::instance.timer->getTicks() + TIME_STEP_INCREASE;
  }
  else {
      // Do nothing
  }

  startByEnter();

  switchStories(iterator, m_story);

}
