#include "Music.hpp"

using namespace engine;

//constructor
Music::Music(){
    gMusic = NULL;
}
//destructor
Music::~Music(){

}
bool Music::loadAudio(std::string music){
    gMusic = Mix_LoadMUS(music.c_str());

    if(gMusic==NULL){
        Log::instance.error("Failed to load audio: " + music);
        return false;
    }

    return true;
}

void Music::playMusic(){
    Mix_PlayMusic(gMusic,-1);
    Mix_ResumeMusic();
}
