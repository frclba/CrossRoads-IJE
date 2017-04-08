#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include "sdl2core.hpp"

#include "Timer.hpp"

namespace engine{

    class Scene{
        public:
            Scene(std::string name = "INVALID_SCENE")
            :scene_name(name), scene_texture(NULL),
            surface_width(0), surface_height(0) {}

            virtual ~Scene(){}

            virtual bool init(SDL_Renderer *);
            virtual bool off();
            virtual bool draw(SDL_Renderer *,Timer *);

            inline std::string name() const { return scene_name; }

        protected:
            std::string scene_name;
            SDL_Texture *scene_texture;
            int surface_width;
            int surface_height;
    };

}

#endif
