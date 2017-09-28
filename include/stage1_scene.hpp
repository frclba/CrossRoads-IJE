/**
    \file stage1_scene.hpp
    This file declares the Stage1Scene class
*/

#ifndef __STAGE1_H__
#define __STAGE1_H__

#include <scene.hpp>

#include "components/animation.hpp"
#include "components/animation_controller.hpp"
#include "components/component.hpp"
#include "player.hpp"

using namespace engine;

/// This class represents the Scene of the first stage
/**
    \class Stage1Scene
    Class responsable for Scene definition of first stage in the game
*/
class Stage1Scene : public Scene {

public:

    Stage1Scene( std::string name ):
               Scene(name),timestep(0){}

    ~Stage1Scene();

    void game_logic();
    void bullet();

private:

    GameObject* ground_stage1;

    GameObject* plataform;
    GameObject* plataform2;
    GameObject* plataform3;

    GameObject* monster1;
    GameObject* monster2;
    GameObject* monster3;
    GameObject* monster4;

    GameObject* portal;
    GameObject* background;

    GameObject *bullet1;
    GameObject *player;
    GameObject* fire_ball;
    GameObject *go_arrow;

    ImageComponent* back_img;

    Player *player_controller;

    bool bulletDir1;
    unsigned int timestep;

    bool is_inside( GameObject* object );

};

#endif // __STAGE1_H__
