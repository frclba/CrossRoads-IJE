#include "Sound.hpp"

using namespace engine;

//TODO -> constructor, desctuctor, Gerenalizando, move music class to music components

//constructor
Sound::Sound(std::string path_to_audio1, std::sting path_to_audio2, std::string path_to_audio3){
    gMenuButton = NULL;
    gJump = NULL;
    gAttack = NULL;

    Sound::loadSound(path_to_audio1);
    Sound::loadSound(path_to_audio2);
    Sound::loadSound(path_to_audio3);
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
    // Mix_ResumeMusic();
}



/** ==================== MUSIC ======================**/
void Music::Music(std::string path_to_music){
  Mix_Music *gMusic = NULL;
  gMusic = Mix_LoadMUS(path_to_music.c_str());
}

void Music::~Music(){
  //Free the music
  Mix_FreeMusic( gMusic );
  gMusic = NULL;
}

void Music::playMusic(){
  if( Mix_PlayingMusic() == 0 ) {
    Mix_PlayMusic( gMusic, -1 );
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
