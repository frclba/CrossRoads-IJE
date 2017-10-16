/**
    \file menu_scene.cpp
    This file implements the MenuScene class
*/
#include "menu_scene.hpp"
#include <assert.h>

/**
    This method is responsible for the logic of the game in the scene menu,
    such as the control buttons and the position of the fire on the screen
*/
void MenuScene::game_logic() {

    // Get menuFire object

    GameObject *menu_fire = &get_game_object("menuFire");
    assert(menu_fire != NULL);

    // Defines the position of the fire on the screen

    menu_fire->main_positionX = 690;
    menu_fire->main_positionY = 470;

    // Managing buttons on the scene

    detect_scene_pass();
    load_button_controller();
    new_game_button_controller();

}

void MenuScene::detect_scene_pass() {

    assert(Game::instance.keyboard != NULL);

    // Mouse over effect

    if( Game::instance.keyboard->isKeyDown("enter") ) {
        Game::instance.change_scene("initial_story");
    }
    else {
        // Do nothing
    }

}

/**
    This method is responsible for the "new game" button control in the
    scene menu.
*/
void MenuScene::new_game_button_controller() {

    // Get new_game_button gameobject

    GameObject *new_game_button = &get_game_object("bNew");
    assert(new_game_button != NULL);

    // Sets the position of the new game button on the screen

    new_game_button->main_positionX = 300;
    new_game_button->main_positionY = 275;

    Animation *new_game_button_animation = (dynamic_cast<Animation*> (
                                new_game_button->get_component("imageBNew")));
    assert(new_game_button_animation != NULL);

    assert(Game::instance.mouse != NULL);

    if( Game::instance.mouse->is_over(new_game_button) ) {
        if( Game::instance.mouse->is_right_button() ) {
            Game::instance.change_scene("initial_story");
        }
        else {
            // Do nothing
        }

        assert(button_hover_in_Sound != NULL);

        button_hover_in_Sound->play(0,-1);

        new_game_button_animation->useAnimation("normal");
    }
    else {
        new_game_button_animation->useAnimation("mouseON");
    }

}

/**
    This method is responsible for the "load" button control in the
    scene menu.
*/
void MenuScene::load_button_controller() {

    // Get load_button gameobject

    GameObject *load_button = &get_game_object("bLoad");
    assert(load_button != NULL);

    // Sets the position of the load button on the screen

    load_button->main_positionX = 300;
    load_button->main_positionY = 400;

    Animation *load_button_animation = (dynamic_cast<Animation*> (
                                 load_button->get_component("imageBLoad")));
    assert(load_button_animation != NULL);

     button_hover_in_Sound = (dynamic_cast<AudioComponent*> (
                          load_button->get_component(
                          "button_hover_sound")));

    assert(Game::instance.mouse != NULL);

    if( Game::instance.mouse->is_over(load_button) ) {
        load_button_animation->useAnimation("normal");

        assert(button_hover_in_Sound != NULL);
        button_hover_in_Sound->play(0,-1);
    }
    else {
        load_button_animation->useAnimation("mouseON");
    }

}

MenuScene::~MenuScene() {}
