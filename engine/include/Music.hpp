#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>

namespace engine{

    class Music{

    public:
        //constructor
        Music();
        //destructor
        ~Music();
        //
        bool loadAudio(std::string);

        void playMusic();



    private:
        //The music that will be played
        Mix_Music *gMusic;

    };

}
