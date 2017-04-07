#include "menu_scene.hpp"
#include "button.hpp"

bool MenuScene::init(SDL_Renderer * main_canvas){
    //Vai disparar a mensagem pré-definida
    SDL_Surface *image = NULL;

    //testing
    player = new Button();
    player->button_sprite->loadMedia(201,215/3, "assets/sprites/button.png", main_canvas);

    fire =  new Sprite();
    fire->loadMedia(174/3,144/2,"assets/sprites/fire.png",main_canvas);

    music = new Music();
    music->loadAudio("assets/music/gm.wav");
    music->playMusic();

    button_grab = new Sound();
    button_grab->loadSound("assets/sounds/button_grab.wav");

    printf("Carregando textura\n");
    image = IMG_Load("assets/sprites/menu.png");

    if(image == NULL){
        log.error("Falha ao carregar imagem!\n");
        return false;
    }

    scene_texture = SDL_CreateTextureFromSurface(main_canvas, image);

    if (scene_texture == NULL){
        log.error("Falha ao criar textura\n");
    }

    surface_width = 800;
    surface_height = 600;

    SDL_FreeSurface(image);
    image = NULL;

    return true;
}

bool MenuScene::off(){
    log.info("Destruindo texturas\n");
    SDL_DestroyTexture(scene_texture);
    scene_texture = NULL;

    return true;
}

bool MenuScene::draw(SDL_Renderer * main_canvas,Timer *timer){
    // printf("Desenhando\n");
    SDL_Rect renderQuad = {0,0, surface_width, surface_height};
    SDL_RenderCopy(main_canvas, scene_texture, NULL, &renderQuad);

    SDL_GetMouseState(&mouseX,&mouseY);

   if(mouseX > 300 && mouseX<(300+201) && mouseY > 300 && mouseY <(300+215/3)){
        player->button_sprite->showImage(300,300,main_canvas,1);
        button_grab->playSound();
   }
   else{
        player->button_sprite->showImage(300,300,main_canvas,0);
   }

    fire->showImage(700,470, main_canvas,timer->getTicks()%6);

    return true;
}
