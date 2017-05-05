#include "stage1_scene.hpp"
    bool canJump = true;

void Stage1Scene::game_logic(){
    GameObject* player = &get_game_object("player");

    int ground = 550;
    int maxJump = 100;
    float gravityDown = 5;
    float gravityUp = gravityDown * 3;

    Animation* idle = (dynamic_cast<Animation *>(player->get_component("playerIdle")));

    //Test if player is not on ground
    if((player->main_positionY + player->main_height) < ground){
        player->main_positionY += gravityDown;
        canJump = false;
    }else{
        canJump = true;
    }

    if(Game::instance.keyboard->isKeyDown(SDLK_d)){
        walkR= true;
    }
    if(Game::instance.keyboard->isKeyDown(SDLK_a)){
        walkL= true;
    }
    if(Game::instance.keyboard->isKeyDown(SDLK_w) && canJump){
        jump = true;
    }else{
        jump = false;
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
        jumptime = Game::instance.timer->getTicks() + maxJump;
    }

    if(Game::instance.timer->getTicks() <= jumptime){
        player->main_positionY -= gravityUp;
    }

}

Stage1Scene::~Stage1Scene(){}
