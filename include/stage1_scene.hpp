#ifndef __STAGE1_H__
#define __STAGE1_H__

#include <scene.hpp>
#include "components/animation.hpp"

using namespace engine;
class Stage1Scene : public Scene{
    public:

        Stage1Scene(std::string name):
            Scene(name){}

        ~Stage1Scene();

    void game_logic();

};

#endif
