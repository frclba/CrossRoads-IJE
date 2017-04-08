#include<iostream>
#include "sdl2core.hpp"

namespace engine{

    class Sound{

    public:
        //constructor
        Sound();
        //destructor
        ~Sound();
        //
        bool loadSound(std::string);

        void playSound();



    private:
        //The music that will be played
        Mix_Chunk *gSound;

    };

}
