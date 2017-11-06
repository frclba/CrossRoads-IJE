/**
    \file menu_scene.cpp
    This file implements the MenuScene class
*/
#include "menu_scene.hpp"
#include <assert.h>

// This line assigns the initial horizontal position to menu fire.
const int INICIAL_POSITION_X_MENU_FIRE = 690;

// This line assigns the initial vertical position to menu fire.
const int INICIAL_POSITION_Y_MENU_FIRE = 470;

// This line assigns the initial horizontal position to new game button.
const int INICIAL_POSITION_X_NEW_GAME_BUTTON = 300;

// This line assigns the initial vertical position to new game button.
const int INICIAL_POSITION_Y_NEW_GAME_BUTTON = 275;

// This line assigns the initial horizontal position to load button.
const int INICIAL_POSITION_X_LOAD_BUTTON = 300;

// This line assigns the initial vertical position to load button.
const int INICIAL_POSITION_Y_LOAD_BUTTON = 400;

/**
    This method is responsible for the logic of the game in the scene menu,
    such as the control buttons and the position of the fire on the screen
*/
void MenuScene::game_logic() {

    // Get menuFire object

    GameObject *menu_fire = &get_game_object("menuFire");
    assert(menu_fire != NULL);

    // Defines the position of the fire on the screen

    menu_fire->main_positionX = INICIAL_POSITION_X_MENU_FIRE;
    menu_fire->main_positionY = INICIAL_POSITION_Y_MENU_FIRE;

    // Managing buttons on the scene

    detect_scene_pass();
    load_button_controller();
    new_game_button_controller();

}

void MenuScene::detect_scene_pass() {

    assert(Game::instance.keyboard != NULL);

    /**
         \note This paragraph is responsible for checking if the enter button
            on keyboard is press, then sets initial story.
    */
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

    new_game_button->main_positionX = INICIAL_POSITION_X_NEW_GAME_BUTTON;
    new_game_button->main_positionY = INICIAL_POSITION_Y_NEW_GAME_BUTTON;

    // Animation to new game button.
    Animation *new_game_button_animation = (dynamic_cast<Animation*> (
                                new_game_button->get_component("imageBNew")));

    assert(new_game_button_animation != NULL);

    assert(Game::instance.mouse != NULL);
 
    /**
         \note This paragraph is responsible for checking if the mouse 
            right button is over of New game button, then sets initial story.
    */
    if( Game::instance.mouse->is_over(new_game_button) ) {
        if( Game::instance.mouse->is_right_button() ) {
            Game::instance.change_scene("initial_story");
        }
        else {
            // Do nothing
        }

        assert(button_hover_in_Sound != NULL);

        button_hover_in_Sound->play(0,-1);

        // Sets 'normal' mode animation to new game button 
        new_game_button_animation->useAnimation("normal");
    }
    else {
        // Sets 'mouseON' mode animation to new game button
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

    load_button->main_positionX = INICIAL_POSITION_X_LOAD_BUTTON;
    load_button->main_positionY = INICIAL_POSITION_Y_LOAD_BUTTON;

    Animation *load_button_animation = (dynamic_cast<Animation*> (
                                 load_button->get_component("imageBLoad")));
                                 
    assert(load_button_animation != NULL);

    button_hover_in_Sound = (dynamic_cast<AudioComponent*> (
                          load_button->get_component(
                          "button_hover_sound")));

    assert(Game::instance.mouse != NULL);

    /**
         \note This paragraph is responsible for checking if the mouse is over
            of Load button, then sets normal animation or 'mouseOn' animation.
    */
    if( Game::instance.mouse->is_over(load_button) ) {

        // Sets 'normal' mode animation to load button
        load_button_animation->useAnimation("normal");

        assert(button_hover_in_Sound != NULL);
        button_hover_in_Sound->play(0,-1);
    }
    else {

        // Sets 'mouseON' mode animation to load button
        load_button_animation->useAnimation("mouseON");
    }

}

MenuScene::~MenuScene() {}
