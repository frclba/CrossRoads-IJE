#include "stage1_scene.hpp"
// ================================================= GAME LOGIC ====================================================
void Stage1Scene::game_logic(){
   ground_stage1 = &get_game_object("ground");
   plataform = &get_game_object("plataform");
   plataform2 = &get_game_object("plataform2");
   plataform3 = &get_game_object("plataform3");

   portal = &get_game_object("portal");
   background = &get_game_object("backgroundForest");
   back_img = (dynamic_cast<ImageComponent *>(background->get_component("backgroundForest")));
   fire_ball = &get_game_object("fireball");

   bullet1 = &get_game_object("bullet");
   player = &get_game_object("player");
   player_controller = (dynamic_cast<Player *>(player->get_component("player_logic")));
  
  
  ground_stage1->main_positionY = 552;
  ground_stage1->main_positionX = 0;
  ground_stage1->main_width = 800;
  ground_stage1->main_height = 200;


  if(back_img->imagePart->x > 2170){
    fire_ball->setState(GameObject::State::enabled);
  }
  else{
    fire_ball->setState(GameObject::State::disabled);
  }


  bullet();
}

void Stage1Scene::bullet(){
  if(player_controller->attack && timestep < Game::instance.timer->getTicks()){
    if(bullet1->state() == GameObject::State::disabled){
      bulletDir1 = player_controller->side;
      bullet1->main_positionX = player->main_positionX + player->main_width;
      bullet1->main_positionY = player->main_positionY;
    }
    timestep = Game::instance.timer->getTicks()+1000;
    bullet1->setState(GameObject::State::enabled);
  }
   
  if(bullet1->state() == GameObject::State::enabled ){
    if(bulletDir1){
      bullet1->main_positionX += 20;
    }
    else{
	
      bullet1->main_positionX -= 20;
    }
  }
  if(bullet1->main_positionX > 800 || bullet1->main_positionX < 0){
    bullet1->setState(GameObject::State::disabled);
      
  }



}

Stage1Scene::~Stage1Scene(){}
