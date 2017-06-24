#include "stage1_scene.hpp"
#include "components/component.hpp"
#include "components/animation_controller.hpp"

// ================================================= GAME LOGIC ====================================================
void Stage1Scene::game_logic(){
  GameObject* ground_stage1 = &get_game_object("ground");
  GameObject* plataform = &get_game_object("plataform");
  GameObject* plataform2 = &get_game_object("plataform2");
  GameObject* plataform3 = &get_game_object("plataform3");

  GameObject* portal = &get_game_object("portal");
  GameObject* background = &get_game_object("backgroundForest");
  ImageComponent* back_img = (dynamic_cast<ImageComponent *>(background->get_component("backgroundForest")));
  GameObject* fire_ball = &get_game_object("fireball");

  
  ground_stage1->main_positionY = 552;
  ground_stage1->main_positionX = 0;
  ground_stage1->main_width = 800;
  ground_stage1->main_height = 200;

  if(back_img->imagePart->x > 800){
    fire_ball->setState(GameObject::State::enabled);
  }

  /*
  plataform->main_positionY = 350;
  plataform->main_positionX = 600;

  plataform2->main_positionY = 200;
  plataform2->main_positionX = 200;

  plataform3->main_positionY = 400;
  plataform3->main_positionX = 100;
  */
}

Stage1Scene::~Stage1Scene(){}
