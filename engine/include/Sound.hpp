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



    private:
        //The music that will be played
        Mix_Chunk *gSound;

    };

}
