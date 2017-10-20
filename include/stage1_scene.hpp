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

    GameObject* ground_stage1 = NULL;

    GameObject* plataform = NULL;
    GameObject* plataform2 = NULL;
    GameObject* plataform3 = NULL;

    GameObject* monster1 = NULL;
    GameObject* monster2 = NULL;
    GameObject* monster3 = NULL;
    GameObject* monster4 = NULL;

    GameObject* portal = NULL;
    GameObject* background = NULL;

    GameObject *bullet1 = NULL;
    GameObject *player = NULL;
    GameObject* fire_ball = NULL;
    GameObject *go_arrow = NULL;

    ImageComponent* back_img = NULL;

    Player *player_controller = NULL;

    bool bulletDir1 = false;
    unsigned int timestep = 0;

    bool is_inside( GameObject* object );
    void bulletAttack();
    void increaseBulletPosition();
    void disableBullet();

};

#endif // __STAGE1_H__
