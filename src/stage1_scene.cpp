#include "stage1_scene.hpp"

// GAME LOGIC

void Stage1Scene::game_logic() {

    ground_stage1 = &get_game_object("ground");

    monster1 = &get_game_object("monster1");
    monster2 = &get_game_object("monster2");
    monster3 = &get_game_object("monster3");
    monster4 = &get_game_object("monster4");

    portal = &get_game_object("portal");
    background = &get_game_object("backgroundForest");
    back_img = (dynamic_cast<ImageComponent*>(
                background->get_component("backgroundForest")));

    fire_ball = &get_game_object("fireball");
    bullet1 = &get_game_object("bullet");

    player = &get_game_object("player");
    player_controller = (dynamic_cast<Player*>(
                         player->get_component("player_logic")));

    go_arrow = &get_game_object("go_arrow");

    ground_stage1->main_positionY = 552;
    ground_stage1->main_positionX = 0;
    ground_stage1->main_width = 800;
    ground_stage1->main_height = 200;

    if( back_img->imagePart->x > 2170 ) {
        back_img->enable_camera = false;
    }
    else {
        fire_ball->setState(GameObject::State::disabled);
    }

    if( ( portal->state() == GameObject::State::enabled &&
        portal->main_positionX + portal->main_width < 800 ) ||
        back_img->imagePart->x > 2190 ||
        is_inside(monster1) ||
        is_inside(monster2) ||
        is_inside(monster3) ||
        is_inside(monster4) ) {
        back_img->enable_camera = false;
        go_arrow->setState(GameObject::State::disabled);
    }
    else {
        back_img->enable_camera = true;
        go_arrow->setState(GameObject::State::enabled);
    }

    bullet();

}

void Stage1Scene::bullet() {

    if( player_controller->attack_ranged &&
        timestep < Game::instance.timer->getTicks() ) {
        if( bullet1->state() == GameObject::State::disabled ) {
            bulletDir1 = player_controller->side;
            bullet1->main_positionX = player->main_positionX +
                                      player->main_width;
            bullet1->main_positionY = player->main_positionY;
        }

        timestep = Game::instance.timer->getTicks() + 500;
        bullet1->setState(GameObject::State::enabled);
    }

    if( bullet1->state() == GameObject::State::enabled ) {
        if( bulletDir1 ) {
            bullet1->main_positionX += 20;
        }
        else {
            bullet1->main_positionX -= 20;
        }
    }
    if( bullet1->main_positionX > 800 || bullet1->main_positionX < 0 ) {
        bullet1->setState(GameObject::State::disabled);
    }

}

bool Stage1Scene::is_inside( GameObject* object ) {
  
    if( object->state() == GameObject::State::enabled &&
      ( object->main_positionX > 0 || object->main_positionX +
                                      object->main_width < 800 ) ) {

        return true;

    }

    return false;

}

Stage1Scene::~Stage1Scene(){

}
