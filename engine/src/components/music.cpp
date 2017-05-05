#include "components/music.hpp"
#include "game.hpp"

using namespace engine;

bool MusicComponent::init(){
    Log::instance.info("Iniciando MusicComponent '" + component_id +"'");
    gMusic = Mix_LoadMUS(main_path.c_str());

    if(gMusic==NULL){
        Log::instance.error("Failed to load audio: " + component_id);
        return false;
    }

    Mix_PlayMusic(gMusic,-1);
    Mix_ResumeMusic();

    return true;
}

bool MusicComponent::shutdown(){
    Log::instance.info("Shutdown MusicComponent");

    return true;
}
