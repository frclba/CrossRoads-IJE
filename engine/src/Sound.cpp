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
    gMusic = Mix_LoadMUS(music.c_str());

    if(gMusic==NULL){
        std::cout << "ERRO to find " + music << std::endl;
        return false;
    }

    return true;
}

void Sound::playMusic(){
    Mix_PlayMusic(gMusic,-1);
    Mix_ResumeMusic();
}
