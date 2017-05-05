#include "mouse.hpp"

using namespace engine ;

//Pega posição do mouse,armazena em x e y e coloca como atributo da classe mouse.
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
