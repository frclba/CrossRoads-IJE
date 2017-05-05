#include "stage1_scene.hpp"

void Stage1Scene::game_logic(){
    GameObject* player = &get_game_object("player");

    Animation* idle = (dynamic_cast<Animation *>(player->get_component("playerIdle")));

    if((player->main_positionY+player->main_height)<550){
        player->main_positionY += 10;
    }
    if(Game::instance.keyboard->isKeyDown(SDLK_d)){
        walkR= true; 
    }
    if(Game::instance.keyboard->isKeyDown(SDLK_a)){
        walkL= true; 
    }
    if(Game::instance.keyboard->isKeyDown(SDLK_w)){
        jump = true; 
    }
    if(Game::instance.keyboard->isKeyDown(SDLK_SPACE)){
        attack = true; 
    }
    if(Game::instance.keyboard->isKeyUp(SDLK_d)){
        walkR= false; 
    }
    if(Game::instance.keyboard->isKeyUp(SDLK_a)){
        walkL= false; 
    }
    if(Game::instance.keyboard->isKeyUp(SDLK_w)){
        jump = false; 
    }
    if(Game::instance.keyboard->isKeyUp(SDLK_SPACE)){
        attack = false; 
    }
    if(walkR && (player->main_positionX+player->main_width)<800){
        idle->useAnimation("walk");
        player->main_positionX += 5;
    }
    else if(walkL && (player->main_positionX)>=0 ){
        idle->useAnimation("walk");
        player->main_positionX -= 5;
    }
    else if(attack){
        idle->useAnimation("attack");
    }
    else{

        idle->useAnimation("stay");
    }


    if(jump){ 
        jumptime = Game::instance.timer->getTicks() + 150; 
    } 
    if(Game::instance.timer->getTicks() <= jumptime){ 
        player->main_positionY -= 20;
    }

}

Stage1Scene::~Stage1Scene(){}
