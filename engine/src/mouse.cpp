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

    int x, y;
    SDL_GetMouseState(&x, &y);
    mouseX = x;
    mouseY = y;

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

    if( mouseX > gameObject->main_positionX &&
        mouseY > gameObject->main_positionY &&
        mouseX < (gameObject->main_width + gameObject->main_positionX) &&
        mouseY < (gameObject->main_height + gameObject->main_positionY) ) {
      return true;
    }
    return false;

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
    return false;
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
    return false;

}
