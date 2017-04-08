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
        Log::instance.error("Failed to load sound: " + music);
        return false;
    }

    return true;
}

void Sound::playSound(){
    Mix_PlayChannel(-1, gSound, 0);
    // Mix_ResumeMusic();
}
