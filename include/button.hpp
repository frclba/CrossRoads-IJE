#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "gameobject.hpp"
#include "Sprite.h"

using namespace engine;

class Button : public GameObject{
    public:
        Button();
        void update(float timer = 0);
        Sprite *button_sprite;
};

#endif
