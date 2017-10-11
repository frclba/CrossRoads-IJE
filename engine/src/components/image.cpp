/**
    \file image.cpp
    ImageComponent class implementation
*/

#include "components/image.hpp"
#include "game.hpp"

using namespace engine;

/**
    Load image file
    \return true if music file loading is successful
    \return false if music file loading fails
*/
bool ImageComponent::init() {

    Log::instance.info("Iniciando componente de imagem: " + main_path);

    if( main_path == "" ) {
        Log::instance.error("Caminho inválido!");

        return false;
    }
    else{

        // Default else.

    }

    /** 
        Save and show image loaded.
    */
    SDL_Surface *image = IMG_Load(main_path.c_str());

    if( image == NULL ) {
        Log::instance.error("Could not load image from path: " + main_path);
    }
    else{

        // Default else.

    }

    main_texture = SDL_CreateTextureFromSurface(Game::instance.main_canvas,
                                                image);

    if( main_texture == NULL ) {
        Log::instance.error("Could not create texture from image");

        return false;
    }
    else{

        // Default else.

    }

    /*
        Pegando os sizes padrões da imagem, por isso precisa ser desenhada no tamanho
        desejado.
    */

    _main_game_object->set_size(image->w, image->h);

    SDL_FreeSurface(image);

    enable_camera = false;

    return true;

}

/**
    /param[int] image_value image displacement - in px
*/
void ImageComponent::set_back_rect(int image_width, int image_height) {

    imagePart = new SDL_Rect();
    imagePart->x = 0;
    imagePart->y = 0;
    imagePart->w = image_width;
    imagePart->h = image_height;

}

/**
    Change horizontal image position
    /param[int] image_value image displacement - in px
*/
void ImageComponent::move_img_rect(int image_value) {

    if( imagePart->x+ imagePart->w + image_value < _main_game_object->main_width &&
        imagePart->x + image_value > 0 && enable_camera ) {
        imagePart->x = imagePart->x + image_value;
    }
    else{

        // Default else.

    }

}

/**
    This method closes ImagesComponent
    \return true
*/
bool ImageComponent::shutdown() {

    Log::instance.info("Shutdown ImageComponent : '" + component_id + "'.");

    SDL_DestroyTexture(main_texture);

    main_texture = NULL;

    return true;

}

/**
    Position image on the screen
*/
void ImageComponent::draw() {

    /** 
        Render image components.
    */
    SDL_Rect *render_quad = new SDL_Rect();

    render_quad->x = _main_game_object->main_positionX;
    render_quad->y = _main_game_object->main_positionY;
    render_quad->w = _main_game_object->main_width;
    render_quad->h = _main_game_object->main_height;


    if( imagePart!=NULL ) {
        render_quad->w = imagePart->w;
        render_quad->h = imagePart->h;
    }
    else{

        // Default else.
        
    }

    SDL_RenderCopy(Game::instance.main_canvas, main_texture, imagePart,
                    render_quad);

}