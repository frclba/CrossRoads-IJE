#include "components/image.hpp"
#include "game.hpp"

using namespace engine;

bool ImageComponent::init(){
    Log::instance.info("Iniciando componente de imagem");

    if(main_path == ""){
        Log::instance.error("Caminho inválido!");
        return false;
    }

    SDL_Surface *image = IMG_Load(main_path.c_str());

    if(image == NULL){
        Log::instance.error("Could not load image from path: " + main_path);
    }

    main_texture = SDL_CreateTextureFromSurface(Game::instance.main_canvas, image);

    if(main_texture == NULL){
        Log::instance.error("Could not create texture from image");
        return false;
    }

    //Pegando os sizes padrões da imagem, por isso precisa ser desenhada no tamanho desejado
    main_game_object->set_size(image->w, image->h);

    SDL_FreeSurface(image);
    return true;
}

bool ImageComponent::shutdown(){
    Log::instance.info("Shutdown ImageComponent");

    SDL_DestroyTexture(main_texture);
    main_texture = NULL;

    return true;
}

void ImageComponent::draw(){
    SDL_Rect renderQuad = {
        main_game_object->main_positionX,
        main_game_object->main_positionY,
        main_game_object->main_width,
        main_game_object->main_height,
    };

    SDL_RenderCopy(Game::instance.main_canvas, main_texture, NULL, &renderQuad);
}
