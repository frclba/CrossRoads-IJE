#include "components/Music.hpp"
#include "game.hpp"

using namespace engine;

//TODO -> constructor, desctuctor, loadMusic, stopMusic, pauseMusic.
bool Music::init(){
    Log::instance.info("Iniciando Music '" + component_id +"'");
    gMusic = Mix_LoadMUS(main_path.c_str());

    if(gMusic == NULL){
        Log::instance.error("Failed to load audio: " + component_id);
        return false;
    }

    Mix_PlayMusic(gMusic,-1);
    Mix_ResumeMusic();

    return true;
}

bool Music::shutdown(){
  //TODO -> write logic to shutdown
    Log::instance.info("Shutdown Music");

    return true;
}
