/**
    \file mouse.hpp
    This file declares the Mouse class
*/

#ifndef MOUSE_H_
#define MOUSE_H_

#include <iostream>
#include "sdl2core.hpp"
#include "gameobject.hpp"


namespace engine {

/// Class for mouse utilities
/**
    \class Mouse
    This class controls all mouse interactions and features
*/
    class Mouse {

    public:
        
        /**
             Declares the contructor, defining the initial values
             of the members.
        */
        Mouse() : mouse_position_x(0), mouse_position_y(0) {};
        ~Mouse();

        // Function to get mouse position

        void set_position();

        // Function to check if the mouse is over of a gameobject

        bool is_over(GameObject *game_object);

        bool is_right_button();

    private:

        bool is_left_button();

        // Mouse position x axis
        int mouse_position_x = 0;

        // Mouse position y axis
        int mouse_position_y = 0;

    };

}

#endif // MOUSE_H_
