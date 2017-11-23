/**
    \file audio.cpp
    AudioComponent class implemantation
*/
#include "components/audio.hpp"
#include "game.hpp"
#include "Logger.hpp"

using namespace engine;

const int LESS_THAN_ONE_NEGAVITE = -5;
const int SUCCESS = 1;

/**
    Load music file
    \return true if music file loading is successful
    \return false if music file loading fails
*/
bool AudioComponent::init() {

    Log::instance.info("Init audio component");

    // verify the type of audio: music or sound, to init properly , in this case validade if is music
    if( m_is_music ) {
        m_music = Mix_LoadMUS(m_audio_path.c_str());

        // Verify if set music is null, in m_music, and treat it.
        if( !valid_music() ) {
            return false;
        }
        else {
            // Do nothing
        }
    }
    // verify the type of audio: music or sound, to init properly, in this case validade if is sound
    else {
        m_sound = Mix_LoadWAV(m_audio_path.c_str());

        // Verify if set music is null, in m_music, and treat it.
        if ( !valid_sound() ){
            return false;
        }
        else {
            // Do nothing
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

    // checks if the audio was started, to play it
    if( m_play_on_start ) {
        play();

        m_play_on_start = false;
    }
    else{

        // Default else.

    }

}

/**
    Play music
    \param[in] loops
    \param[in] channel
*/
void AudioComponent::play(int loops, int channel) {

    assert(loops >= -1);
    assert(channel >= -1);

    // Checks if there is a music to play the seted music
    if( m_is_music ) {
        play_music(loops);
    }
    // If there isan't a music, the sound will be played
    else {
        if(play_sound(loops, channel) == LESS_THAN_ONE_NEGAVITE){
            Log::instance.error("Fail in play sound, loops or channel with invalid value");
            return;
        }
    }

    // Checks if there isan't a music to change the audio state.
    if( !m_is_music ) {
        m_audio_state = AudioState::stopped;
    }
    else{

        // Default else.

    }

}

/**
    Ends playback of a song on a particular output channel
    \param channel
*/
void AudioComponent::stop(int channel) {

    assert(channel >= -1);

    // Checks if there is a music to halt the seted music
    if( m_is_music ) {
        Mix_HaltMusic();
    }
    // If there isan't a music, the sound will be halted
    else {
        Mix_HaltChannel(channel);
    }

    m_audio_state = AudioState::stopped;

    Log::instance.info("the audio was stopped");
}

/**
    Pauses playback of a song on a particular output channel
    \param channel
*/
void AudioComponent::pause(int channel) {

    assert(channel >= -1);

    // Checks if there is a music to pause the seted music
    if( m_is_music ) {
      Mix_PauseMusic();
    }
    // If there isan't a music, the sound will be paused
    else {
      Mix_Pause( channel );
    }

    m_audio_state = AudioState::paused;

    Log::instance.info("music has been paused");

}

bool AudioComponent::valid_music() {

    // Checks if attribute that stores the music isan't null, points to success.
    if( m_music != NULL ) {
        return true;
    }
    // if attribute that stores the music is null, points to error.
    else {
        Log::instance.error("Music not found!");
        return false;
    }

}

bool AudioComponent::valid_sound() {

    // Checks if attribute that stores the sound isan't null, points to success.
    if ( m_sound != NULL ){
        return true;
    }
    // if attribute that stores the sound is null, points to error.
    else {
        Log::instance.error("Sound not found: " + m_audio_path);
        return false;
    }

}

void AudioComponent::play_music(int loops) {

    assert(loops >= -1);

    // Checks if audio state is stopped to play the music.
    if( m_audio_state == AudioState::stopped ) {
        Mix_PlayMusic(m_music, loops);
    }
    // Checks if audio state is paused to resume the music.
    else if( m_audio_state == AudioState::paused ) {
        Mix_ResumeMusic();
    }
    else {
        // Do nothing
    }

    m_audio_state = AudioState::playing;
    Log::instance.info("music was started");
}


int AudioComponent::play_sound(int loops, int channel) {

    // Checks if loops anf chennel are infinite or larger than 0, points to error
    // for less then one negative.
    if(loops >= -1 || channel >= -1){
        return LESS_THAN_ONE_NEGAVITE;
    }else{
        // Checks if audio state is stopped to get error and point.
        if( m_audio_state == AudioState::stopped ) {
            std::string error = Mix_GetError();

            // Checks if playchennel return -1 to treat a error.
            if(Mix_PlayChannel(channel, m_sound, loops) == -1){
                Log::instance.error("Mix_PlayChannel:" + error);
            }
        }
        // Checks if audio state is paused to resume.
        else if( m_audio_state == AudioState::paused ) {
            Mix_Resume(channel);
        }
        else {
            // Do nothing
        }

        return SUCCESS;
    }



    m_audio_state = AudioState::playing;
    Log::instance.info("sound was started");
}
