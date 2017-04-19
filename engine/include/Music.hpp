#include<iostream>
#include "sdl2core.hpp"

namespace engine{

    class Music{

    public:
        Music();
        ~Music();

        //Load music audio on memory, if success return true
        bool loadAudio(std::string);

        //Start music on call
        void playMusic();

    private:
        //The music that will be played
        Mix_Music *gMusic;
    };
}
