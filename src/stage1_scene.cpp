#include "stage1_scene.hpp"
#include "components/component.hpp"
#include "components/animation_controller.hpp"

// ================================================= GAME LOGIC ====================================================
void Stage1Scene::game_logic(){
  GameObject* ground_stage1 = &get_game_object("ground");
  GameObject* plataform = &get_game_object("plataform");
  
  ground_stage1->main_positionY = 552;
  ground_stage1->main_positionX = 0;
  ground_stage1->main_width = 800;
  ground_stage1->main_height = 200;

  plataform->main_positionY = 400;
  plataform->main_positionX = 400;
}

Stage1Scene::~Stage1Scene(){}
