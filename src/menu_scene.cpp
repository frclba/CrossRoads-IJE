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

    music = new Sound;
    music->loadAudio("assets/music/gm.wav");
    music->playMusic();

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

    Button *player = new Button();
    // surface_width = image->w;
    // surface_height = image->h;
    surface_width = 800;
    surface_height = 600;

    SDL_FreeSurface(image);
    image = NULL;
    // button_sprite = new Sprite();


    // Button *player = new Button();
    // player->button_sprite->loadMedia(180,247, "../assets/sprites/personagem.png", main_canvas);
    // player->button_sprite->showImage(30,30,main_canvas,0);
    //GameObject o;

    return true;
}

bool MenuScene::off(){
    printf("Destruindo texturas\n");
    SDL_DestroyTexture(scene_texture);
    scene_texture = NULL;

    return true;
}

bool MenuScene::draw(SDL_Renderer * main_canvas,Timer *timer){
    printf("Desenhando\n");
    SDL_Rect renderQuad = {0,0, surface_width, surface_height};
    SDL_RenderCopy(main_canvas, scene_texture, NULL, &renderQuad);

    SDL_GetMouseState(&mouseX,&mouseY);  

   if(mouseX > 300 && mouseX<(300+201) && mouseY > 300 && mouseY <(300+215/3)){
        player->button_sprite->showImage(300,300,main_canvas,1);
   }
   else{
        player->button_sprite->showImage(300,300,main_canvas,0);
   }    
//    SDL_Delay(100);
    fire->showImage(700,470, main_canvas,timer->getTicks()%6);

    return true;
}
