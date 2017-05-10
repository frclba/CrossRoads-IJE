#include "stage1_scene.hpp"
#include "components/component.hpp"

bool canJump = true;
bool jump = false;
bool isFalling = false;

void Stage1Scene::game_logic(){
    GameObject* player = &get_game_object("player");

    int ground = 552;
    int maxHeight = 200;
    float gravity = 13;
    float moveForce = 7;

    Animation* idle = (dynamic_cast<Animation *>(player->get_component("playerIdle")));
    Animation* running = (dynamic_cast<Animation *>(player->get_component("playerRunning")));
    Animation* damage = (dynamic_cast<Animation *>(player->get_component("playerDamage")));

    idle->main_state = Component::State::enabled;
    running->main_state = Component::State::disabled;
    damage->main_state = Component::State::disabled;


//========================== JUMP LOGIC ======================================
    //Player try jump and he can jump
    if(Game::instance.keyboard->isKeyDown(SDLK_w) && canJump){
        jump = true;
    }

    if(jump){
        if(player->main_positionY >= (ground - maxHeight)){
            player->main_positionY -= gravity;
            isFalling = false;
        }else{
            jump = false;
            isFalling = true;
        }
    }

    //Test if player is not on ground
    if(isFalling){
        if((player->main_positionY + player->main_height) < ground){
            player->main_positionY += gravity;
            canJump = false;
        }else{
            canJump = true;
        }

}

//===========================================================================

    if(Game::instance.keyboard->isKeyDown(SDLK_d)){
        walkR= true;
    }
    if(Game::instance.keyboard->isKeyDown(SDLK_a)){
        walkL= true;
    }

    if(Game::instance.keyboard->isKeyDown(SDLK_SPACE)){
        attack = true;
    }
    if(Game::instance.keyboard->isKeyDown(SDLK_q)){
        damageBool = true;
    }
    if(Game::instance.keyboard->isKeyUp(SDLK_d)){
        walkR= false;
    }
    if(Game::instance.keyboard->isKeyUp(SDLK_a)){
        walkL= false;
    }
    if(Game::instance.keyboard->isKeyUp(SDLK_q)){
        damageBool = false;
    }
    // if(Game::instance.keyboard->isKeyUp(SDLK_w)){
        // jump = false;
    // }

    if(Game::instance.keyboard->isKeyUp(SDLK_SPACE)){
        attack = false;
    }
    if(walkR && (player->main_positionX+player->main_width)<800){
        idle->main_state = Component::State::disabled;
        running->main_state = Component::State::enabled;

        player->main_positionX += moveForce;
    }
    else if(walkL && (player->main_positionX)>=0 ){
        idle->main_state = Component::State::disabled;
        running->main_state = Component::State::enabled;

        player->main_positionX -= moveForce;
    }
    else if(damageBool){
        idle->main_state = Component::State::disabled;
        running->main_state = Component::State::disabled;
        damage->main_state = Component::State::enabled;
    }
    else if(attack){

        // idle->useAnimation("attack");
    }
    else{

        // idle->useAnimation("stay");
    }

    // if(jump){
    //     jumptime = Game::instance.timer->getTicks() + maxHeight;
    // }
    //
    // if(Game::instance.timer->getTicks() <= jumptime){
    //     player->main_positionY -= gravity;
    // }


}

Stage1Scene::~Stage1Scene(){}
