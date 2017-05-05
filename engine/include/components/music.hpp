#ifndef __ENGINE_COMPONENTS_MUSIC__
#define __ENGINE_COMPONENTS_MUSIC__

#include<iostream>

#include "sdl2core.hpp"
#include "components/component.hpp"
#include "gameobject.hpp"

namespace engine{
    class MusicComponent : public Component {
        public:
            MusicComponent(GameObject &main_game_object, std::string id, std::string path)
            : Component(main_game_object, id), main_path(path){}

            ~MusicComponent(){};

            bool init();
            bool shutdown();

            //Load music audio on memory, if success return true
            bool loadAudio(std::string);

            //Start music on call
            void playMusic();

        private:
            std::string main_path;
            //The music that will be played
            Mix_Music *gMusic;
    };
}

#endif
