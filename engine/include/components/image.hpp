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
            ImageComponent(GameObject &main_game_object, std::string image_id, std::string image_path)
                           : Component(main_game_object, image_id), main_path(image_path) {

                // Default function call.

            }

            ~ImageComponent() {

                // Default function call.

            };

            bool init();
            bool shutdown();

            void move_img_rect(int image_value);
            void set_back_rect(int image_width, int image_height);
            virtual void draw();

            /** 
                Control react of image. 
            */
            SDL_Rect* imagePart;

            /** 
                Control camera enabling to move or not. 
            */
            bool enable_camera = false;

        protected:
            /** 
                Image image_path. 
            */
            std::string main_path = "";

            /** 
                Image texture controlled by SDL.
            */
            SDL_Texture *main_texture;

    };

}

#endif // FOO_BAR_ENGINE_COMPONENTS_IMAGE_H_
