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
        std::cout << "ERRO to find " + music << std::endl;
        return false;
    }

    return true;
}

void Music::playMusic(){
    Mix_PlayMusic(gMusic,-1);
    Mix_ResumeMusic();
}
