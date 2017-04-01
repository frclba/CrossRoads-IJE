#include "menu_scene.hpp"

bool MenuScene::init(SDL_Renderer * main_canvas){
    //Vai disparar a mensagem pré-definida
    SDL_Surface *image = NULL;

    printf("Carregando textura\n");
    image = IMG_Load("assets/sprites/menu.png");

    if(image == NULL){
        printf("Falhou ao carregar imagem !\n");
        return false;
    }

    scene_texture = SDL_CreateTextureFromSurface(main_canvas, image);

    if (scene_texture == NULL){
        printf("Falha ao criar textura\n");
    }

    // surface_width = image->w;
    // surface_height = image->h;
    surface_width = 800;
    surface_height = 600;

    SDL_FreeSurface(image);
    image = NULL;

    //GameObject o;
    
    return true;
}

bool MenuScene::off(){
    printf("Destruindo texturas\n");
    SDL_DestroyTexture(scene_texture);
    scene_texture = NULL;

    return true;
}

bool MenuScene::draw(SDL_Renderer * main_canvas){
    printf("Desenhando\n");
    SDL_Rect renderQuad = {0,0, surface_width, surface_height};
    SDL_RenderCopy(main_canvas, scene_texture, NULL, &renderQuad);

    return true;
}
