#include "mouse.hpp"

using namespace engine ;

void Mouse::set_position(){
    int x,y;
    SDL_GetMouseState(&x, &y);
    mouseX = x;
    mouseY = y;
}

bool Mouse::is_over(engine::GameObject *gameObject){

    if(
            mouseX > gameObject->main_positionX &&
            mouseY > gameObject->main_positionY &&
            mouseX < (gameObject->main_width + gameObject->main_positionX) &&
            mouseY < (gameObject->main_height + gameObject->main_positionY)
    )
    {
        return true;
    }
    return false;
}
bool Mouse::is_right_button(){
    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        return true;
    }
    return false;
}
bool Mouse::is_left_button(){
    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        return true;
    }
    return false;
}
