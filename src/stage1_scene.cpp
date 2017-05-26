#include "stage1_scene.hpp"
#include "components/component.hpp"
#include "components/animation_controller.hpp"

bool canJump = true;
bool jump = false;
bool isFalling = false;
bool isRight = true;

int ground = 552;
int maxHeight = 200;
float gravity = 1;
float jumpF = 20;
float moveForce = 7;
float monster_move = 4;

float dy = 0;

void Stage1Scene::setup(){
    player = &get_game_object("player");
    plataform = &get_game_object("plataform");
    //monster = &get_game_object("monster");
    plataform->main_positionY = 400;
    plataform->main_positionX = 400;
    // auto animCtrl = player->get_component("animation_controller");
    // idle = (dynamic_cast<Animation *>(player->get_component("playerIdle")));
    // running = (dynamic_cast<Animation *>(player->get_component("playerRunning")));
    // damage = (dynamic_cast<Animation *>(player->get_component("playerDamage")));
    // attackComp = (dynamic_cast<Animation *>(player->get_component("playerAttack")));

}
// ================================================= GAME LOGIC ====================================================
void Stage1Scene::game_logic(){

    setup();
    animCtrl = (dynamic_cast<AnimationControllerComponent *>(player->get_component("animationController")));
    //monster_controler = (dynamic_cast<AnimationControllerComponent *>(monster->get_component("monster_controler")));

    animCtrl->play_animation("player_idle");
    // animCtrl->play_animation("player_attack");
    gravityF();
    jump_player();
    move_player();
    attack_player();
    processPos();
    // damage_player(player, animCtrl);

    //gravityF(monster);
    //processPos(monster);
    //    monsterAI(monster);
}

// // =================================================== DAMAGE LOGIC =================================================
// void Stage1Scene::damage_player(GameObject *player, AnimationControllerComponent *animCtrl){
//
//     if(Game::instance.keyboard->isKeyUp(SDLK_q)){
//         damageBool = false;
//     }
//
//     if(Game::instance.keyboard->isKeyDown(SDLK_q)){
//         damageBool = true;
//     }
//
//     if(damageBool){
//         // idle->main_state = Component::State::disabled;
//         // running->main_state = Component::State::disabled;
//         // attackComp->main_state = Component::State::disabled;
//         // damage->main_state = Component::State::enabled;
//         animCtrl->play_animation("player_damage");
//     }
//
// }
//
// // ============================================= ATTACK LOGIC ===================================================
void Stage1Scene::attack_player(){

    if(Game::instance.keyboard->isKeyDown(SDLK_SPACE)){
        attack = true;
    }

  if(Game::instance.keyboard->isKeyUp(SDLK_SPACE)){
    attack = false;
  }

    if(attack){
        animCtrl->play_animation("player_attack");
    }else{

  }
}

// // ============================================== MOVE LOGIC ===================================================
void Stage1Scene::move_player(){
//     //Detect move right
    if(Game::instance.keyboard->isKeyDown(SDLK_d)){
        walkR= true;
    }
    if(Game::instance.keyboard->isKeyUp(SDLK_d)){
        walkR= false;
    }
//
    //Detect move left
    if(Game::instance.keyboard->isKeyDown(SDLK_a)){
        walkL= true;
    }
    if(Game::instance.keyboard->isKeyUp(SDLK_a)){
        walkL= false;
    }
//
    if(walkR && (player->main_positionX+player->main_width)<800){
        isRight = true;
	animCtrl->play_animation("player_running");
        animCtrl->flipping(true);
	player->main_positionX += moveForce;

    } else if(walkL && (player->main_positionX)>=0 ){
        isRight = false;
        animCtrl->play_animation("player_running");
        animCtrl->flipping(false);
        player->main_positionX -= moveForce;
    }
}
//
/*// //=========================================== JUMP LOGIC==========================================
void Stage1Scene::jump_player(GameObject *player){
    //Player try jump and he can jump
    if(Game::instance.keyboard->isKeyDown(SDLK_w) && canJump){
        jump = true;
    }

  if(jump){
    if(m_player->main_positionY >= (ground - maxHeight)){
      m_player->main_positionY -= gravity;
      isFalling = false;
    }else{
      jump = false;
      isFalling = true;
    }
  }

  //Test if player is not on ground
  if(isFalling){
    if((m_player->main_positionY + m_player->main_height) < ground){
      m_player->main_positionY += gravity;
      canJump = false;
    }
    else{
      canJump = true;
    }
  }
}
*/


//
// //=========================================== JUMP LOGIC==========================================
void Stage1Scene::jump_player(){
    //Player try jump and he can jump

  if(Game::instance.keyboard->isKeyDown(SDLK_w) && (dy==0)){
	dy -= jumpF;
    }
}

void Stage1Scene::processPos()
{
     player->main_positionY += dy;   // current velocity components.
}


void Stage1Scene::gravityF(){
  if ( (player->main_positionY + player->main_height) <= ground ){      // If the player is not on the platform
    dy += gravity;
  }

  else{
    dy = 0;
  }
  if(player->checkCollision(plataform) && dy > 0 &&(player->main_positionY + player->main_height) > plataform->main_positionY){
    dy = 0;
  }
}

/*void Stage1Scene::monsterAI(GameObject* obj){
  monster->main_positionY = ground - monster->main_height;
  monster_controler->play_animation("monster_walk");
  if(player->main_positionX > obj->main_positionX){
    monster_controler->flipping(true);
    obj->main_positionX += monster_move;
  }
  else{
    monster_controler->flipping(false);
    obj->main_positionX -= monster_move;
  }

  if(obj->checkCollision(player)){
    animCtrl->play_animation("player_damage");
  }

  }*/

Stage1Scene::~Stage1Scene(){}
