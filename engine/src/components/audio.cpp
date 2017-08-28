#include "components/audio.hpp"
#include "game.hpp"
#include "Logger.hpp"
using namespace engine;

bool AudioComponent::init() {
    Log::instance.info("Init audio component");
    if (m_is_music) {
        // m_music = Game::instance.assets_manager().load_music(m_path);
        m_music = Mix_LoadMUS(m_path.c_str());

        if (m_music == NULL) {
            Log::instance.error("Music not found!");
            return false;
        }
    }
    else{
        m_sound = Mix_LoadWAV(m_path.c_str());

        if (m_sound == NULL) {
            Log::instance.error("Sound not found: " + m_path);
            return false;
        }
    }

    return true;
}

bool AudioComponent::shutdown() {
    Log::instance.info("Shutdown audio component");
    return true;
}

void AudioComponent::update() {
    if (m_play_on_start) {
        play();
        m_play_on_start = false;
    }
}

void AudioComponent::play(int loops, int channel) {
    if (m_is_music) {
        if (m_audio_state == AudioState::stopped)
            Mix_PlayMusic(m_music, loops);
        else if (m_audio_state == AudioState::paused)
            Mix_ResumeMusic();
    }
    else {
        if (m_audio_state == AudioState::stopped)
            Mix_PlayChannel(channel, m_sound, loops);
        else if (m_audio_state == AudioState::paused)
            Mix_Resume(channel);
    }

    m_audio_state = AudioState::playing;

    if (!m_is_music)
        m_audio_state = AudioState::stopped;
}

void AudioComponent::stop(int channel) {
    if (m_is_music)
        Mix_HaltMusic();
    else
        Mix_HaltChannel(channel);

    m_audio_state = AudioState::stopped;
}

void AudioComponent::pause(int channel) {
    if (m_is_music)
      Mix_PauseMusic();
    else
      Mix_Pause(channel);

    m_audio_state = AudioState::paused;
}
