#include "Keyboard.hpp"

using namespace engine;
//const Uint8 *(Keyboard::Keyboard_State) = SDL_GetKeyboardState(nullptr);

Keyboard::Keyboard(){

}
Keyboard::~Keyboard(){

}
void Keyboard::setKeys(SDL_Event* evt){
    if(evt->type == SDL_KEYDOWN){
        keycode_down.push_back(evt->key.keysym.sym);
    }
    else if(evt->type == SDL_KEYUP){
        keycode_up.push_back(evt->key.keysym.sym);
    }
}




bool Keyboard::isKeyDown(Uint8 key){
    for(auto m_key : keycode_down){
        if(m_key == key){
            return true;
        }
    }
    return false;

}
bool Keyboard::isKeyUp(Uint8 key){    
    for(auto m_key : keycode_up){
        if(m_key == key){
            return true;
        }
    }
    return false;
}


void Keyboard::clearKeyboard(){
   keycode_up.clear();
   keycode_down.clear();
}
