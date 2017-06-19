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
  Restart(GameObject &main_game_object, std::string id):
    Component(main_game_object, id){}

    ~Restart();

    bool init();
    void update();

private:

};

#endif
