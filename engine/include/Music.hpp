#include<iostream>
#include "sdl2core.hpp"

namespace engine{

    class Music{

    public:
        Music();
        ~Music();

        bool loadAudio(std::string);
        void playMusic();

    private:
        //The music that will be played
        Mix_Music *gMusic;
    };
}
