#include "Sound.hpp"

using namespace engine;

//constructor
Sound::Sound(){
    gSound = NULL;
}
//destructor
Sound::~Sound(){

}

bool Sound::loadSound(std::string music){
    gSound = Mix_LoadWAV(music.c_str());

    if(gSound==NULL){
        std::cout << "ERRO to find " + music << std::endl;
        return false;
    }

    return true;
}

void Sound::playSound(){
    Mix_PlayChannel(-1, gSound, 0);
    // Mix_ResumeMusic();
}
