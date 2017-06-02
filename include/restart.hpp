#ifndef __RESTART_HPP__
#define __RESTART_HPP__
#include <iostream>

#include "components/component.hpp"
#include "components/animation_controller.hpp"
#include "game.hpp"
#include "Logger.hpp"

using namespace engine;

class Restart : public Component{
public:
  Restart(GameObject &_main_game_object, std::string component_id):
    Component(_main_game_object,component_id){}

    ~Restart();

    bool init();
    void update();

private:

};

#endif
