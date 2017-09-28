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

    // If the timer is running and isn't already paused

    if( mStarted && !mPaused ) {

        // Pause the timer

        mPaused = true;

        // Calculate the paused ticks

        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
    else{
        // Do nothing
    }

}

/**
    This method is responsable
    for unpause clock action
*/
void Timer::unpause() {

    // If the timer is running and paused

    if( mStarted && mPaused ) {

        // Unpause the timer

        mPaused = false;

        // Reset the starting ticks

        mStartTicks = SDL_GetTicks() - mPausedTicks;

        // Reset the paused ticks

        mPausedTicks = 0;
    }
    else{
        // Do nothing
    }

}

// Gets the timer's time

Uint32 Timer::getTicks() {

    // The actual timer time

    Uint32 time = 0;

    // If the timer is running

    if( mStarted ) {

        // If the timer is paused

        if( mPaused ) {

            // Return the number of ticks when the timer was paused

            time = mPausedTicks;
        }
        else {

            // Return the current time minus the start time

            time = SDL_GetTicks() - mStartTicks;
        }
    }
    else{
        // Do nothing
    }

    return time;

}

/**
    This method is responsable
    for checks the status of the timer
    \return mStarted true
*/
bool Timer::isStarted() {

    // Timer is running and paused or unpaused

    return mStarted;

}

/**
    This method is responsable
    for checks the status of the timer
    \return mPaused and mStarted true
*/
bool Timer::isPaused() {

    // Timer is running and paused

    return mPaused && mStarted;

}

/**
    This method is responsable
    for defines the passing of time
*/
void Timer::set_TimeStep() {

    timeStep = getTicks();

}

Uint32 Timer::get_elapseTime() {

    return getTicks() - timeStep;

}
