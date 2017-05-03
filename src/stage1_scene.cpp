#include "stage1_scene.hpp"

void Stage1Scene::game_logic(){
  GameObject* player = &get_game_object("player");

  player->main_positionX = 300;
  player->main_positionY = 300;

  // Animation* idle = (dynamic_cast<Animation *>(player->get_component("playerIdle")));
  // idle->useAnimation("idle");

}

Stage1Scene::~Stage1Scene(){}
