#include "menu_scene.hpp"

void MenuScene::game_logic(){

    //pega objeto menuFire
    GameObject* fireMenu = &get_game_object("menuFire");
    //define a posicao do fogo na tela
    fireMenu->main_positionX = 690;
    fireMenu->main_positionY = 470;

    //pega gameobject bNew
    GameObject* bNew = &get_game_object("bNew");
    //define a posicao do botao novo jogo na tela
    bNew->main_positionX = 300;
    bNew->main_positionY = 200;

    //pega gameobject bLoad
    GameObject* bLoad = &get_game_object("bLoad");
    //define a posicao do botao de load na tela
    bLoad->main_positionX = 300;
    bLoad->main_positionY = 320;

    //pega componentes de animacao do botao novo e do botao load
    Animation* bnewAnimation = (dynamic_cast<Animation *>(bNew->get_component("imageBNew")));
    Animation* bloadAnimation = (dynamic_cast<Animation *>(bLoad->get_component("imageBLoad")));

    //Hover Animation button New
    if(Game::instance.mouse->is_over(bNew)){
        bnewAnimation->useAnimation("normal");
    }
    else{
        bnewAnimation->useAnimation("mouseON");
    }
    //Hover Animation button Load
    if(Game::instance.mouse->is_over(bLoad)){
        bloadAnimation->useAnimation("normal");
    }
    else{
        bloadAnimation->useAnimation("mouseON");
    }
}


MenuScene::~MenuScene(){}
