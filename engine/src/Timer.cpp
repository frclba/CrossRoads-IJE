/**
    \file Time.cpp
    This file declares the Timer class
*/
#include "Timer.hpp"

using namespace engine;

Timer::Timer() {

    timeStep = 0;
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;

}

Timer::~Timer() {

}

/**
    This method is responsable
    for start clock action
*/
void Timer::start() {

    // Start the timer

    mStarted = true;

    // Unpause the timer

    mPaused = false;

    // Get the current clock time

    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;

}

/**
    This method is responsable
    for stop clock action
*/
void Timer::stop() {

    // Stop the timer

    mStarted = false;

    // Unpause the timer

    mPaused = false;

    // Clear tick variables

    mStartTicks = 0;
    mPausedTicks = 0;

}

/**
    This method is responsable
    for pause clock action
*/
void Timer::pause() {

    /**
         \note This paragraph is responsible for checking if the timer is
            running and isn't already paused, then pause the timer
            and calculate the paused ticks
    */
    if( mStarted == true && mPaused == false) {

        // Pause the timer

        mPaused = true;

        // Calculate the paused ticks

        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }

}

/**
    This method is responsable
    for unpause clock action
*/
void Timer::unpause() {

    /**
         \note This paragraph is responsible for checking if the timer
            is running and paused, then reset the starting ticks
            and reset the paused ticks.
    */
    if( mStarted == true && mPaused == true) {

        // Unpause the timer

        mPaused = false;

        // Reset the starting ticks

        mStartTicks = SDL_GetTicks() - mPausedTicks;

        // Reset the paused ticks

        mPausedTicks = 0;
    }

}

// Gets the timer's time

Uint32 Timer::getTicks() {

    // The actual timer time

    Uint32 time = 0;

    /**
         \note This paragraph is responsible for checking if the timer
            is running, then if the timer is paused, return the number
            of ticks when the timer was paused, if isn't, return
            the current time minus the start time.
    */
    if( mStarted == true ) {

        // If the timer is paused

        if( mPaused == true ) {

            // Return the number of ticks when the timer was paused

            time = mPausedTicks;
        }
        else {

            // Return the current time minus the start time

            time = SDL_GetTicks() - mStartTicks;
        }
    }
    else {
      // Do nothing
    }

    return time;

}

/**
    This method is responsable
    for checks the status of the timer
    \return mStarted true
*/
bool Timer::is_started() {

    // Timer is running and paused or unpaused

    if( mStarted == true ){
      return true;
    }
    else{
      return false;
    }

}

/**
    This method is responsable
    for checks the status of the timer
    \return mPaused and mStarted true
*/
bool Timer::is_paused() {

    // Timer is running and paused

    if( mPaused == true && mStarted == true){
      return true;
    }
    else{
      return false;
    }

}

/**
    This method is responsable
    for defines the passing of time
*/
void Timer::set_TimeStep() {

    timeStep = getTicks();

}

Uint32 Timer::get_elapseTime() {

    Uint32 elapse_time = getTicks() - timeStep;

    return elapse_time;

}
