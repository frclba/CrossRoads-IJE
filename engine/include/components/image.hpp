#ifndef __ENGINE_COMPONENTS_IMAGE__
#define __ENGINE_COMPONENTS_IMAGE__

#include<string>
#include<utility>
#include<sdl2core.hpp>

#include "components/component.hpp"
#include "gameobject.hpp"

namespace engine{
    class ImageComponent : public Component {
        public:
            ImageComponent(GameObject &main_game_object, std::string id, std::string path)
            : Component(main_game_object, id), main_path(path){}

            ~ImageComponent(){};

            bool init();
            bool shutdown();

            virtual void draw();

        protected:
            //Caminho da imagem
            std::string main_path;

            //Olhar nesse ponto para utilizar nossa pŕopria classe.
            SDL_Texture *main_texture;

            SDL_Rect* imagePart = NULL;
    };
}

#endif
