#ifndef __ENGINE_COMPONENTS_SOUND__
#define __ENGINE_COMPONENTS_SOUND__

#include<iostream>
#include "sdl2core.hpp"
#include "components/component.hpp"
#include "gameobject.hpp"

namespace engine{
    class Sound : public Component {
      public:
        //constructor
        Sound(GameObject &main_game_object, std::string id, std::string path)
        : Component(main_game_object, id), main_path(path){}

        //destructor
        ~Sound(){};

        bool init();
        bool shutdown();

        //Load audio file on memory
        bool loadSound(std::string);

        //Play audio on call
        void playSound();

    protected:
        std::string main_path;

        //The sound that will be played
        Mix_Chunk* gSound;
    };

    // class Music{
    // public:
    //   Music(std::string path_to_music);    // Initialize Music
    //   ~Music();                                   // Destroys Music
    //
    //   bool loadMusic(std::string music_name);     // Loads Music Into Memory
    //   void playMusic();                           // Plays Music
    //   void pauseMusic();
    //   void stopMusic();
    //
    // private:
    //   Mix_Music *gSoundMusic;
    //
    // };
}

#endif
