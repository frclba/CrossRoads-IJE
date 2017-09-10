#ifndef FOO_BAR_ENGINE_COMPONENTS_AUDIO_H_
#define FOO_BAR_ENGINE_COMPONENTS_AUDIO_H_

#include <iostream>

#include "sdl2core.hpp"
#include "components/component.hpp"
#include "gameobject.hpp"

namespace engine {

    class AudioComponent : public Component {

        public:
            enum class AudioState {

                playing,
                paused,
                stopped

            };

            AudioComponent(GameObject &main_game_object, std::string id, std::string path,
                           bool is_music = false, bool play_on_start = true)
                : Component(main_game_object, id), m_path(path), m_is_music(is_music), 
                  m_play_on_start(play_on_start), m_audio_state(AudioState::stopped),
                  m_music(NULL), m_sound(NULL) {

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
            std::string m_path;
            bool m_is_music;
            bool m_play_on_start;
            AudioState m_audio_state;

            Mix_Music * m_music;
            Mix_Chunk * m_sound;

    };

}

#endif // FOO_BAR_ENGINE_COMPONENTS_AUDIO_H_
