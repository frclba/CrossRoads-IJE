#include "Sound.hpp"

using namespace engine;

//constructor
Sound::Sound(){
    gMenuButton = NULL;
    gJump = NULL;
    gAttack = NULL;
}

//destructor
Sound::~Sound(){
  Mix_FreeChunk( gMenuButton );
  Mix_FreeChunk( gJump );
  Mix_FreeChunk( gAttack );

  gMenuButton = NULL;
  gJump = NULL;
  gAttack = NULL;
}

bool Sound::loadSound(std::string path_to_audio, Mix_Chunk* global_sound_ptr){
    bool success = true;

    global_sound_ptr = Mix_LoadWAV(path_to_audio.c_str());
    if(global_sound_ptr == NULL){
        Log::instance.error("Failed to load sound: gMenuButton");
        success = false;
    }

    return success;
}

void Sound::playSound(){
    Mix_PlayChannel(-1, gSound, 0);
    // Mix_ResumeMusic();
}
