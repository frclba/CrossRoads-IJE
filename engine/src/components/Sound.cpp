#include "components/Sound.hpp"


using namespace engine;

//TODO -> constructor, desctuctor, Gerenalizando, move music class to music components

bool Sound::init(){
  Log::instance.info("Iniciando Sound '" + component_id +"'");
  gSound = Mix_LoadWAV(main_path.c_str());
  if(gSound == NULL){
    Log::instance.warning("Sound component '" + component_id +"' wasn't Initialized.");
    return false;
  }
  return true;
}

bool Sound::shutdown(){
  Log::instance.info("Shuting-down Sound '" + component_id +"' component.");
  Mix_FreeChunk( gSound );
  gSound = NULL;
  return true;
}

void Sound::playSound(){
    Mix_PlayChannel(-1, gSound, 0);
}

// /** ==================== MUSIC ======================**/
// Music::Music(std::string path_to_music){
//   gSoundMusic = NULL;
//   gSoundMusic = Mix_LoadMUS(path_to_music.c_str());
// }
//
// Music::~Music(){
//   //Free the music
//   Mix_FreeMusic( gSoundMusic );
//   gSoundMusic = NULL;
// }
//
// void Music::playMusic(){
//   if( Mix_PlayingMusic() == 0 ) {
//     Mix_PlayMusic( gSoundMusic, -1 );
//   }
//   else {
//     if( Mix_PausedMusic() == 1 ) {
//       Mix_ResumeMusic();
//     }
//     else {
//       Mix_PauseMusic();
//     }
//   }
// }
//
// void Music::stopMusic(){
//   //Stop the music
//   Mix_HaltMusic();
// }
