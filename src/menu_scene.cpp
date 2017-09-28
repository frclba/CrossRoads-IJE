/**
    \file menu_scene.cpp
    This file implements the MenuScene class
*/
#include "menu_scene.hpp"

/**
    This method is responsible for the logic of the game in the scene menu,
    such as the control buttons and the position of the fire on the screen
*/
void MenuScene::game_logic() {

    // Get menuFire object

    GameObject *fireMenu = &get_game_object("menuFire");

    // Defines the position of the fire on the screen

    fireMenu->main_positionX = 690;
    fireMenu->main_positionY = 470;

    // Managing buttons on the scene

    buttons_controller();

}

/**
    This method is responsible for the button controls in the
    scene menu, such as the new game button and load game button.
*/
void MenuScene::buttons_controller() {

    // Mouse over effect

    if( Game::instance.keyboard->isKeyDown("enter") ) {
        Game::instance.change_scene("initial_story");
    }
    else {
        // Do nothing
    }

    // Get bNew gameobject

    GameObject *bNew = &get_game_object("bNew");

    // Sets the position of the new game button on the screen

    bNew->main_positionX = 300;
    bNew->main_positionY = 275;

    // Get bLoad gameobject

    GameObject *bLoad = &get_game_object("bLoad");

    // Sets the position of the load button on the screen

    bLoad->main_positionX = 800;
    bLoad->main_positionY = 820;

    Animation *bnewAnimation = (dynamic_cast<Animation*> (
                                bNew->get_component("imageBNew")));

    if( Game::instance.mouse->is_over(bNew) ) {
        if( Game::instance.mouse->is_right_button() ) {
            Game::instance.change_scene("initial_story");
        }
        else {
            // Do nothing
        }

        AudioComponent *button_hover_sound = (dynamic_cast<AudioComponent*> (
                                              bLoad->get_component(
                                              "button_hover_sound")));

        bnewAnimation->useAnimation("normal");
        button_hover_sound->play(0,-1);
    }
    else {
        bnewAnimation->useAnimation("mouseON");
    }

    Animation *bloadAnimation = (dynamic_cast<Animation*> (
                                 bLoad->get_component("imageBLoad")));

    if( Game::instance.mouse->is_over(bLoad) ) {
        bloadAnimation->useAnimation("normal");
    }
    else {
        bloadAnimation->useAnimation("mouseON");
    }

}

MenuScene::~MenuScene() {}
