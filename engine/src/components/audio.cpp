/**
    \file audio.cpp
    AudioComponent class implemantation
*/
#include "components/audio.hpp"
#include "game.hpp"
#include "Logger.hpp"

using namespace engine;

/**
    Load music file
    \return true if music file loading is successful
    \return false if music file loading fails
*/
bool AudioComponent::init() {

    Log::instance.info("Init audio component");

    if( m_is_music ) {
        m_music = Mix_LoadMUS(m_path.c_str());

        if( m_music == NULL ) {
            Log::instance.error("Music not found!");

            return false;
        }
    }
    else {
        m_sound = Mix_LoadWAV(m_path.c_str());

        if ( m_sound == NULL ){
            Log::instance.error("Sound not found: " + m_path);

            return false;
        }
    }

    return true;

}

/**
    This method closes the AudioComponent in the game
    \return true
*/
bool AudioComponent::shutdown() {

    Log::instance.info("Shutdown audio component");

    return true;

}

/**
    Play music if it has not already been started
*/
void AudioComponent::update() {

    if( m_play_on_start ) {
        play();

        m_play_on_start = false;
    }

}

/**
    Play music
    \param[in] loops
    \param[in] channel
*/
void AudioComponent::play(int loops, int channel) {

    if( m_is_music ) {
        if( m_audio_state == AudioState::stopped ) {
            Mix_PlayMusic(m_music, loops);
        }
        else if( m_audio_state == AudioState::paused ) {
            Mix_ResumeMusic();

        }
    }
    else {
        if( m_audio_state == AudioState::stopped ) {
            Mix_PlayChannel(channel, m_sound, loops);
        }
        else if( m_audio_state == AudioState::paused ) {
            Mix_Resume(channel);
        }
    }

    m_audio_state = AudioState::playing;

    if( !m_is_music ) {
        m_audio_state = AudioState::stopped;
    }

}

/**
    Ends playback of a song on a particular output channel
    \param channel
*/
void AudioComponent::stop(int channel) {

    if( m_is_music ) {
        Mix_HaltMusic();
    }
    else {
        Mix_HaltChannel(channel);
    }

    m_audio_state = AudioState::stopped;

}

/**
    Pauses playback of a song on a particular output channel
    \param channel
*/
void AudioComponent::pause(int channel) {

    if( m_is_music ) {
      Mix_PauseMusic();
    }
    else {
      Mix_Pause( channel );
    }

    m_audio_state = AudioState::paused;

}
