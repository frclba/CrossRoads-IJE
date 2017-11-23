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

        void update();

    private:
        bool init();

        //  Story that will start an animation
        AnimationControllerComponent *m_story;

        // Used to mark the time step
        unsigned int time_step;

        /**
            Iterator used to choose an animation of the story
            according to the time step
        */
        unsigned int story_iterator;

};

#endif  // _INITIAL_STORY_HPP_
