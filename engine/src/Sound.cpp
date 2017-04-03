#include "Sound.hpp"

using namespace engine;

//constructor
Sound::Sound(){
    gMusic = NULL;    
}
//destructor
Sound::~Sound(){

}
bool Sound::loadAudio(std::string music){
    gMusic = Mix_LoadMUS("assets/music/gm.wav");

    if(gMusic==NULL){
        std::cout << "ERRO to find " + music << std::endl;
    }
}

void Sound::playMusic(){
    Mix_PlayMusic(gMusic,-1);
}


