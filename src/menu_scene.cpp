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

    GameObject *menu_fire = &get_game_object("menuFire");

    // Defines the position of the fire on the screen

    menu_fire->main_positionX = 690;
    menu_fire->main_positionY = 470;

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

    // Get new_game_button gameobject

    GameObject *new_game_button = &get_game_object("bNew");

    // Sets the position of the new game button on the screen

    new_game_button->main_positionX = 300;
    new_game_button->main_positionY = 275;

    // Get load_button gameobject

    GameObject *load_button = &get_game_object("bLoad");

    // Sets the position of the load button on the screen

    load_button->main_positionX = 800;
    load_button->main_positionY = 820;

    Animation *new_game_button_animation = (dynamic_cast<Animation*> (
                                new_game_button->get_component("imageBNew")));

    if( Game::instance.mouse->is_over(new_game_button) ) {
        if( Game::instance.mouse->is_right_button() ) {
            Game::instance.change_scene("initial_story");
        }
        else {
            // Do nothing
        }

        AudioComponent *button_hover_sound = (dynamic_cast<AudioComponent*> (
                                              load_button->get_component(
                                              "button_hover_sound")));

        new_game_button_animation->useAnimation("normal");
        button_hover_sound->play(0,-1);
    }
    else {
        new_game_button_animation->useAnimation("mouseON");
    }

    Animation *load_button_animation = (dynamic_cast<Animation*> (
                                 load_button->get_component("imageBLoad")));

    if( Game::instance.mouse->is_over(load_button) ) {
        load_button_animation->useAnimation("normal");
    }
    else {
        load_button_animation->useAnimation("mouseON");
    }

}

MenuScene::~MenuScene() {}
