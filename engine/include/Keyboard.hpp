/**
    \file keyboard.hpp
    This file declares Keyboard class
*/

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include<iostream>
#include<list>
#include <algorithm>
#include <unordered_map>

#include "sdl2core.hpp"

#define F_JBUTTON 0
#define SPACE_JBUTTON 1
#define W_JBUTTON 2
#define RETURN_JBUTTON 9

#define HORIZONTAL_JAXIS 0
#define VERTICAL_JAXIS 1
#define POSITIVE_JAXIS 8000
#define NEGATIVE_JAXIS -8000

namespace engine {

    /// Class for keyboard control
    /**
        \class Keyboard
        This class is responsible to map, listen and set keys pressed
    */
    class Keyboard {
        public:
            Keyboard();
            ~Keyboard();

            /**
                Set keys
                \param key this parameter define new event in game
                \return anything because the routine is void
            */
            void setKeys( SDL_Event* key );

            /**
                Verify key down
                \param key this parameter verify if key pressed is down
                \return returns bool to key down or not
            */
            bool isKeyDown( std::string key );

            /**
                Verify key up
                \param key this parameter verify if key pressed is up
                \return returns bool to key up or not
            */
            bool isKeyUp( std::string key );

            /**
                Clear key down and key up pressed by the player    
            */
            void clearKeyboard();

        private:
            /**
                Map all invalid and valid keys pressed by the player and
                what they do in game
            */
            void create_keyboard_mapping();

            /**
                List of keyboard keys pressed by the player
            */
            std::list <Uint8> keycodes_down;

            /**
                List of keyboard keys released by the player
            */
            std::list <Uint8> keycodes_up;

            /**
              Hash to map keyboard key names to SDL_Keycode
            */
            std::unordered_map<std::string, int> m_button_code;

    };

}

#endif
