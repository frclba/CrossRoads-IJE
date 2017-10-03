/**
    \file mouse.cpp
    This file define methods content of the Mouse class
*/

#include "mouse.hpp"

using namespace engine;

/**
    Get mouse position
*/
void Mouse::set_position() {

    // Receives the coordinate of the x axis
    int x_axis = 0;

    // Receives the coordinate of the y axis
    int y_axis = 0;
    SDL_GetMouseState(&x_axis, &y_axis);
    mouse_position_x = x_axis;
    mouse_position_y = y_axis;

}

/**
    Check if mouse cursor is over a defined object
    \param *gameObject
    \parblock
        Is a input parameter that represents an object of the game(!=NULL)
    \endparblock
    \return true is over
    \return false isn't over
*/
bool Mouse::is_over(engine::GameObject *gameObject) {

    if( mouse_position_x > gameObject->main_positionX &&
        mouse_position_y > gameObject->main_positionY &&
        mouse_position_x < (gameObject->main_width + 
                            gameObject->main_positionX) &&
        mouse_position_y < (gameObject->main_height + 
                            gameObject->main_positionY) ) {
        return true;
    }
    else {
        return false;
    }

}

/**
    Check if mouse click is right button
    \return true is right button
    \return false isn't right button
*/
bool Mouse::is_right_button() {

    if( SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) ) {
        return true;
    }
    else {
        return false;
    }
    
}

/**
    Check if mouse click is left button
    \return true is left button
    \return false isn't left button
*/
bool Mouse::is_left_button() {

    if( SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT) ) {
        return true;
    }
    else {
        return false;
    }

}
