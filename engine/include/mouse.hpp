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

        Mouse() : mouseX(0), mouseY(0) {};
        ~Mouse();

        // Function to get mouse position

        void set_position();

        // Function to check if the mouse is over of a gameobject

        bool is_over(GameObject *gameObject);
        bool is_right_button();
        bool is_left_button();

        // Mouse position

        int mouseX;
        int mouseY;

    private:

    };

}

#endif // MOUSE_H_
