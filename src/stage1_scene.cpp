#include "stage1_scene.hpp"
#include "components/component.hpp"

bool canJump = true;
bool jump = false;
bool isFalling = false;
bool isRight = true;

int ground = 552;
int maxHeight = 200;
float gravity = 13;
float moveForce = 7;

void Stage1Scene::setup(){
    player = &get_game_object("player");

    idle = (dynamic_cast<Animation *>(player->get_component("playerIdle")));
    running = (dynamic_cast<Animation *>(player->get_component("playerRunning")));
    damage = (dynamic_cast<Animation *>(player->get_component("playerDamage")));
    attackComp = (dynamic_cast<Animation *>(player->get_component("playerAttack")));
}

// ================================================= GAME LOGIC ====================================================
void Stage1Scene::game_logic(){
    setup();
    // Animation* idle = (dynamic_cast<Animation *>(player->get_component("playerIdle")));
    // Animation* running = (dynamic_cast<Animation *>(player->get_component("playerRunning")));
    // Animation* damage = (dynamic_cast<Animation *>(player->get_component("playerDamage")));
    // Animation* attackComp = (dynamic_cast<Animation *>(player->get_component("playerAttack")));

    // idle = (dynamic_cast<Animation *>(player->get_component("playerIdle")));
    // running = (dynamic_cast<Animation *>(player->get_component("playerRunning")));
    // damage = (dynamic_cast<Animation *>(player->get_component("playerDamage")));
    // attackComp = (dynamic_cast<Animation *>(player->get_component("playerAttack")));

    idle->main_state = Component::State::enabled;
    running->main_state = Component::State::disabled;
    damage->main_state = Component::State::disabled;
    attackComp->main_state = Component::State::disabled;

    running->flipping(isRight);
    idle->flipping(isRight);
    attackComp->flipping(isRight);
    damage->flipping(isRight);

    jump_player(player);
    move_player(player);
    attack_player(player);
    damage_player(player);

}

// =================================================== DAMAGE LOGIC =================================================
void Stage1Scene::damage_player(GameObject *player){

    if(Game::instance.keyboard->isKeyUp(SDLK_q)){
        damageBool = false;
    }

    if(Game::instance.keyboard->isKeyDown(SDLK_q)){
        damageBool = true;
    }

    if(damageBool){
        idle->main_state = Component::State::disabled;
        running->main_state = Component::State::disabled;
        attackComp->main_state = Component::State::disabled;
        damage->main_state = Component::State::enabled;
    }


}

// ============================================= ATTACK LOGIC ===================================================
void Stage1Scene::attack_player(GameObject *player){

    if(Game::instance.keyboard->isKeyDown(SDLK_SPACE)){
        attack = true;
    }

    if(Game::instance.keyboard->isKeyUp(SDLK_SPACE)){
        attack = false;
    }

    if(attack){
        idle->main_state = Component::State::disabled;
        running->main_state = Component::State::disabled;
        damage->main_state = Component::State::disabled;
        attackComp->main_state = Component::State::enabled;
    } else{

    }
}

// ============================================== MOVE LOGIC ===================================================
void Stage1Scene::move_player(GameObject *player){
    //Detect move right
    if(Game::instance.keyboard->isKeyDown(SDLK_d)){
        walkR= true;
    }
    if(Game::instance.keyboard->isKeyUp(SDLK_d)){
        walkR= false;
    }

    //Detect move left
    if(Game::instance.keyboard->isKeyDown(SDLK_a)){
        walkL= true;
    }
    if(Game::instance.keyboard->isKeyUp(SDLK_a)){
        walkL= false;
    }

    if(walkR && (player->main_positionX+player->main_width)<800){
        isRight = true;
        idle->main_state = Component::State::disabled;
        damage->main_state = Component::State::disabled;
        attackComp->main_state = Component::State::disabled;
        running->main_state = Component::State::enabled;

        player->main_positionX += moveForce;
    } else if(walkL && (player->main_positionX)>=0 ){
        isRight = false;
        idle->main_state = Component::State::disabled;
        damage->main_state = Component::State::disabled;
        attackComp->main_state = Component::State::disabled;
        running->main_state = Component::State::enabled;

        player->main_positionX -= moveForce;
    }
}

//=========================================== JUMP LOGIC==========================================
void Stage1Scene::jump_player(GameObject *player){
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
}

Stage1Scene::~Stage1Scene(){}
