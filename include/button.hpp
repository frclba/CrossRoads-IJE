/**
    \file button.hpp
    This file declares Button class
*/
#ifndef FOO_BAR_BUTTON_H_
#define FOO_BAR_BUTTON_H_

#include "gameobject.hpp"

#include "Sprite.h"

using namespace engine;

/// Class for button control
/**
    \class Button
    This class is responsible to update game every time a button is pressed
*/
class Button : public GameObject {

    public:
        Button();
        /**
    		Update game
    		\param timer this parameter make game update
    		\return anything because the routine is void
		*/
        void update(float timer = 0);
        
        Sprite *button_sprite;

};

#endif // FOO_BAR_BUTTON_H_
