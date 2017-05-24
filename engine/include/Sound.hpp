#include<iostream>
#include "sdl2core.hpp"

namespace engine{

    class Sound{
      public:
        //constructor
        Sound();
        //destructor
        ~Sound();

        //Load audio file on memory
        bool loadSound(std::string);

        //Play audio on call
        void playSound();

        void pauseSound();
        void resumeSound();

        std::string audio_name;

    protected:
        //The music that will be played
        Mix_Chunk* gMenuButton;
        Mix_Chunk* gJump;
        Mix_Chunk* gAttack;

        std::string path_to_audio;
    };

    class Music{
    public:
      Music();

      ~Music();

      bool loadMusic(std::string music_name);

      void playMusic();

      void pauseMusic();

      void stopMusic();
    private:
      Mix_Music *gMusic;

    };
}
