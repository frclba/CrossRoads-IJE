#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include "sdl2core.hpp"

#include "Timer.hpp"
//Tornar toda abstrata

namespace engine{

class Scene{
        public:
            // inline Scene(std::string name = "INVALID_SCENE")
            // :scene_name(name), scene_texture(NULL),
            // surface_width(0), surface_height(0) {}

            Scene(std::string name = "INVALID_SCENE")
            :scene_name(name), scene_texture(NULL),
            surface_width(0), surface_height(0) {}

            virtual ~Scene(){}
            virtual bool init(SDL_Renderer *main_canvas);
            virtual bool off();

            virtual bool draw(SDL_Renderer *main_canvas,Timer* timer);

            inline std::string name() const { return scene_name; }

        protected:
            std::string scene_name;
            SDL_Texture *scene_texture;
            int surface_width;
            int surface_height;

    };

}

#endif
