#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace engine{

class GameObject{
        public:
            virtual ~GameObject();
            virtual void render();
            virtual void update(float timer) = 0;
        private:

    };

}

#endif
