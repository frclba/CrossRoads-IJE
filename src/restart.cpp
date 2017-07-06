#include "restart.hpp"

bool Restart::init(){return true;}

// ================================================= GAME LOGIC ====================================================
void Restart::update(){

    if(Game::instance.keyboard->isKeyDown("enter")){
        Game::instance.change_scene("Main Menu");
    }

}

Restart::~Restart(){}
