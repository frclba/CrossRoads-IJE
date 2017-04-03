#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>

namespace engine{

    class Sound{

        public:
            //constructor
            Sound();
            //destructor
            ~Sound();
            //
            bool loadAudio(std::string);

            void playMusic();



        private:
            //The music that will be played
            Mix_Music *gMusic;

    };

}
