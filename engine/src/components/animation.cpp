#include"components/animation.hpp"

using namespace engine;

Animation::~Animation(){

}

bool Animation::init(){

    Log::instance.info("Iniciando componente de animacao");

    if(main_path == ""){
        Log::instance.error("Caminho inválido!");
        return false;
    }

    SDL_Surface *image = IMG_Load(main_path.c_str());

    if(image == NULL){
        // SDL_IMG_ERROR("Could not load image from path !" << main_path);
    }

    main_texture = SDL_CreateTextureFromSurface(Game::instance.main_canvas, image);

    if(main_texture == NULL){
        // SDL_ERROR("Could not create texture from image");
        return false;
    }

    //Pegando os sizes padrões da imagem, por isso precisa ser desenhada no tamanho desejado
    _main_game_object->set_size(m_widthDiv, m_heightDiv);

    SDL_FreeSurface(image);

    //divide imagem
    //ler matriz de imagems em um arquivo
    int cont = 0;
    for (int h = 0; h < image->h && cont < m_num_image; h += m_heightDiv) {
        for(int w = 0; w < image->w && cont < m_num_image; w += m_widthDiv){
            SDL_Rect *rect = new SDL_Rect();
            rect->x = w;
            rect->y = h;
            rect->w = m_widthDiv;
            rect->h = m_heightDiv;
            imageVector.push_back(rect);
            cont++;
        }
    }

    main_animation[BEGIN] = 0;
    main_animation[END] = imageVector.size()-1;


    return true;
}

void Animation::setAnimation(std::string animationName,int begin,int end){
    (animationMap[animationName])[BEGIN] = begin;
    (animationMap[animationName])[END] = end;
}

bool Animation::useAnimation(std::string animationName){

    main_animation[BEGIN] = (animationMap[animationName])[BEGIN];
    main_animation[END] = (animationMap[animationName])[END];
    if(main_frame<main_animation[BEGIN] || main_frame>main_animation[END]){
        main_frame = main_animation[BEGIN];
    }

    return true;
}

void Animation::setDelay(int toSetDelay){
    this->delay = toSetDelay;
}

void Animation::flipping(bool isFlip){
  if(isFlip){
    flip = SDL_FLIP_HORIZONTAL;
  }else{
    flip = SDL_FLIP_NONE;
  }
}

bool Animation::has_finished(){
  if(main_frame == main_animation[END]){
    return true;
  }
  return false;
}

void Animation::setup(){
  _main_game_object->set_size(m_widthDiv, m_heightDiv);
}

void Animation::draw(){

    SDL_Rect *renderQuad = new SDL_Rect();
    renderQuad->x = _main_game_object->main_positionX;
    renderQuad->y = _main_game_object->main_positionY;
    renderQuad->w = imageVector[main_frame]->w;
    renderQuad->h = imageVector[main_frame]->h;

    if((int)(Game::instance.timer->getTicks() - timestep) >= delay){
        main_frame++;
        timestep = Game::instance.timer->getTicks();
    }

    if(main_frame > main_animation[END]){
            main_frame = main_animation[BEGIN];
    }

    SDL_RenderCopyEx(Game::instance.main_canvas, main_texture, imageVector[main_frame] , renderQuad, 0, NULL, flip);
}

