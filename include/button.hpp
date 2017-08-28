#ifndef FOO_BAR_BUTTON_H_
#define FOO_BAR_BUTTON_H_

#include "gameobject.hpp"

#include "Sprite.h"

using namespace engine;

class Button : public GameObject {

    public:
        Button();
        void update( float timer = 0 );
        
        Sprite *button_sprite;

};

#endif // FOO_BAR_BUTTON_H_
