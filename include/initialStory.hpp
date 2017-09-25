/**
    \file initialStory.hpp
    This file declares the InitialStory class
*/
#ifndef _INITIAL_STORY_HPP_
#define _INITIAL_STORY_HPP_

#include <iostream>
#include <vector>

#include "game.hpp"
#include "gameobject.hpp"
#include "components/component.hpp"
#include "components/animation_controller.hpp"

using namespace engine;

/**
    \class InitialStory
    This class is responsible for create a story initial in the game
*/


class InitialStory : public Component{

public:
    InitialStory( GameObject &main_game_object, std::string id, 
                  AnimationControllerComponent* story ):

        Component(main_game_object, id),m_story(story){}

        ~InitialStory();

        bool init();

        void update();

private:
    AnimationControllerComponent *m_story;

    unsigned int timestep = 0;
    unsigned int interator = 0;
  
};

#endif  // _INITIAL_STORY_HPP_
