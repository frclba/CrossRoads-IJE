/**
    \file audio.hpp
    This file contains header declaration for AudioComponent class
*/

#ifndef FOO_BAR_ENGINE_COMPONENTS_AUDIO_H_
#define FOO_BAR_ENGINE_COMPONENTS_AUDIO_H_

#include <iostream>
#include "sdl2core.hpp"
#include "components/component.hpp"
#include "gameobject.hpp"

namespace engine {

    /// Managing audio components
    /**
        \class AudioComponent
        This class manages the audio components and exchanges between them
    */
    class AudioComponent : public Component {

        public:
            enum class AudioState {

                playing,
                paused,
                stopped

            };

            AudioComponent(GameObject &main_game_object, std::string audio_id, std::string audio_path,
                           bool is_music = false, bool play_on_start = true) :
                           Component(main_game_object, audio_id), m_audio_path(audio_path), m_is_music(is_music), 
                           m_play_on_start(play_on_start), m_audio_state(AudioState::stopped),
                           m_music(NULL), m_sound(NULL) {

                // Default function call.

            }

            bool init();
            bool shutdown();
            void update();

            void play(int loops = -1, int channel = -1);
            void stop(int channel = -1);
            void pause(int channel = -1);

            inline bool is_music() {

                return m_is_music;

            }

        private:
            /** 
                audio_path of musics and sounds of the game. 
            */
            std::string m_audio_path = "";

            /** 
                Control time when music and sound will be played. 
            */
            bool m_is_music = false;
            bool m_play_on_start = false;

            /** 
                Control state of musics and sound of the game. 
            */
            AudioState m_audio_state;

            /** 
                Control music and sound of game. 
            */
            Mix_Music * m_music;
            Mix_Chunk * m_sound;

    };

}

#endif // FOO_BAR_ENGINE_COMPONENTS_AUDIO_H_