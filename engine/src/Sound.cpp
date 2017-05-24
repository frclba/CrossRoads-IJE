#include "Sound.hpp"

using namespace engine;

//TODO -> constructor, desctuctor, Gerenalizando, move music class to music components

//constructor
Sound::Sound(std::string path_to_audio){
    gSound = NULL;
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
    Mix_PlayChannel(-1, gMenuButton, 0);
}


/** ==================== MUSIC ======================**/
Music::Music(std::string path_to_music){
  gSoundMusic = NULL;
  gSoundMusic = Mix_LoadMUS(path_to_music.c_str());
}

Music::~Music(){
  //Free the music
  Mix_FreeMusic( gSoundMusic );
  gSoundMusic = NULL;
}

void Music::playMusic(){
  if( Mix_PlayingMusic() == 0 ) {
    Mix_PlayMusic( gSoundMusic, -1 );
  }
  else {
    if( Mix_PausedMusic() == 1 ) {
      Mix_ResumeMusic();
    }
    else {
      Mix_PauseMusic();
    }
  }
}

void Music::stopMusic(){
  //Stop the music
  Mix_HaltMusic();
}
