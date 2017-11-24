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

    if( valid_main_path() ) {

        /**
            Save and show image loaded.
        */
        SDL_Surface *image = IMG_Load(main_path.c_str());

        valid_image(image);

        main_texture = SDL_CreateTextureFromSurface(Game::instance.main_canvas,
                                                    image);

        if( valid_main_texture() ) {

             /*
                Take the default image size to draw it
            */
            _main_game_object->set_size(image->w, image->h);

            SDL_FreeSurface(image);

            enable_camera = false;

            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

/**
    /param[int] image_value image displacement - in px
*/
void ImageComponent::set_back_rect(int image_width, int image_height) {

    assert(image_width >= 0);
    assert(image_height >= 0);

    image_measures = new SDL_Rect();

    /*
        Sets a new position for the image object
    */
    image_measures->x = INITIAL_SCREEN_POSITION;
    image_measures->y = INITIAL_SCREEN_POSITION;
    image_measures->w = image_width;
    image_measures->h = image_height;

}

/**
    Change horizontal image position
    /param[int] image_value image displacement - in px
*/
void ImageComponent::move_img_rect(int displacement) {

    assert(displacement >= 0);

    if( valid_image_position(displacement) && enable_camera ) {
        image_measures->x = image_measures->x + displacement;
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

    /**
        Get current _main_game_objetc values
    */
    render_quad->x = _main_game_object->main_positionX;
    render_quad->y = _main_game_object->main_positionY;
    render_quad->w = _main_game_object->main_width;
    render_quad->h = _main_game_object->main_height;


    /**
        If image_measures is not null, it updates the value of the new
        drawing with the measurements of the image.
    */
    if( valid_image_measures() ) {
        render_quad->w = image_measures->w;
        render_quad->h = image_measures->h;
    }
    else {

        // Default else.
    }

    SDL_RenderCopy(Game::instance.main_canvas, main_texture, image_measures,
                    render_quad);

}

/**
    Valid if image path isn't null
    \return true if image path is valid
*/
bool ImageComponent::valid_main_path() {

    if( main_path != "" ) {
        return true;
    }
    else {
        Log::instance.error("Caminho inválido!");
        return false;
    }

}

/**
    Valid if image isn't null
    \return true if image is valid
*/
bool ImageComponent::valid_image(SDL_Surface *image) {

    assert(image != NULL);

    if( image != NULL ) {
        return true;
    }
    else {
        Log::instance.error("Could not load image from path: " + main_path);
        return false;
    }

}

/**
    Valid if texture isn't null
    \return true if texture is valid
*/
bool ImageComponent::valid_main_texture() {

    if( main_texture != NULL ) {
        return true;
    }
    else {
        Log::instance.error("Could not create texture from image");
        return false;
    }

}

/**
    Valid if object with the image measurements isn't null
    \return true if object is valid
*/
bool ImageComponent::valid_image_measures() {

    if( image_measures != NULL ) {
        return true;
    }
    else {
        Log::instance.error("image without measurements");
        return false;
    }

}

/**
    Valid if new image position is valid
    \return true if new image position is valid
*/
bool ImageComponent::valid_image_position(int displacement) {

    assert(displacement >= 0);

    if ( image_measures->x + image_measures->w + displacement <
         _main_game_object->main_width && image_measures->x +
         displacement > INITIAL_SCREEN_POSITION ) {
        return true;
    }
    else {
        Log::instance.error("image in wrong position");
        return false;
    }

}
