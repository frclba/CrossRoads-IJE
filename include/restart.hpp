/**
    \file restart.hpp
    This file declares the restart class
*/
#ifndef __RESTART_HPP__
#define __RESTART_HPP__

#include <iostream>

#include "components/component.hpp"
#include "components/animation_controller.hpp"
#include "game.hpp"
#include "Logger.hpp"

using namespace engine;

/**
    \class Restart
    This class is responsible for restart in the game
*/

class Restart : public Component{
	
	public:
    	Restart( GameObject &main_game_object, std::string id ):
        	Component( main_game_object, id ){}

        ~Restart();

        void update();

	private:
		bool init();

};

#endif  // __RESTART_HPP__
