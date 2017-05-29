#ifndef __STAGE1_H__
#define __STAGE1_H__

#include <scene.hpp>
#include "components/animation.hpp"
#include "components/animation_controller.hpp"

using namespace engine;

class Stage1Scene : public Scene{
    public:

   Stage1Scene(std::string name):
     Scene(name){}//, jumptime(0), walkR(false), walkL(false), jump(false), attack(false), damageBool(false){}


    ~Stage1Scene();


  void game_logic();

    private:
};

#endif
