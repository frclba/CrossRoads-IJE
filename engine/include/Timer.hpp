/**
    \file Time.hpp
    This file declares the Timer class
*/
#ifndef TIMER_H_
#define TIMER_H_

#include <iostream>

#include "sdl2core.hpp"

namespace engine {

    /// Class for game time control
    /**
        \class Time
        This class is responsible for managing of game time
    */
    class Timer {

        public:
            Timer();

            ~Timer();

            // The various clock actions
            
            void start();
            void stop();
            void pause();
            void unpause();

            // Gets the timer's time

            Uint32 getTicks();

            void set_TimeStep();
            Uint32 get_elapseTime();

        private:
            // Checks the status of the timer

            bool isStarted();
            bool isPaused();

            // The clock time when the timer started

            Uint32 mStartTicks;

            // The ticks stored when the timer was paused

            Uint32 mPausedTicks;

            Uint32 timeStep;

            // The timer status

            bool mPaused;
            bool mStarted;

    };

}

#endif // TIMER_H_
