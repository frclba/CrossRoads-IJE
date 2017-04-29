#include "menu_scene.hpp"

void MenuScene::game_logic(){

    GameObject* fireMenu = &get_game_object("menuFire");
    fireMenu->main_positionX = 690;
    fireMenu->main_positionY = 470;
   
    GameObject* bNew = &get_game_object("bNew");
    bNew->main_positionX = 300;
    bNew->main_positionY = 200;

    GameObject* bLoad = &get_game_object("bLoad");
    bLoad->main_positionX = 300;
    bLoad->main_positionY = 320;

    Animation* bnewAnimation = (dynamic_cast<Animation *>(bNew->get_component("imageBNew")));
    Animation* bloadAnimation = (dynamic_cast<Animation *>(bLoad->get_component("imageBLoad")));

    if(Game::instance.mouse->is_over(bNew)){
        bnewAnimation->useAnimation("normal");
    }
    else{

        bnewAnimation->useAnimation("mouseON");
    }
    if(Game::instance.mouse->is_over(bLoad)){
        bloadAnimation->useAnimation("normal");
    }
    else{
        bloadAnimation->useAnimation("mouseON");
    }
}


MenuScene::~MenuScene(){}
