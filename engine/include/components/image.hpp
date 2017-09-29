/**
    \file image.hpp
    This file contains header declaration for ImageComponent class
*/

#ifndef FOO_BAR_ENGINE_COMPONENTS_IMAGE_H_
#define FOO_BAR_ENGINE_COMPONENTS_IMAGE_H_

#include <string>
#include <utility>

#include "sdl2core.hpp"
#include "components/component.hpp"
#include "gameobject.hpp"

namespace engine{

    /// Settings related to an image
    /**
        \class ImageComponent
        This has the structure regarding the management of an image in the game
    */
    class ImageComponent : public Component {

        public:
            ImageComponent(GameObject &main_game_object, std::string id, std::string path)
                           : Component(main_game_object, id), main_path(path) {

                // Default function call.

            }

            ~ImageComponent() {

                // Default function call.

            };

            bool init();
            bool shutdown();

            void move_img_rect(int value);
            void set_back_rect(int width, int height);
            virtual void draw();

            SDL_Rect* imagePart;

            bool enable_camera = false;

        protected:
            //Caminho da imagem.
            std::string main_path = "";

            //Olhar nesse ponto para utilizar nossa pŕopria classe.
            SDL_Texture *main_texture;

    };

}

#endif // FOO_BAR_ENGINE_COMPONENTS_IMAGE_H_
