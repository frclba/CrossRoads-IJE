#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include<iostream>
#include<list>
#include <algorithm>
#include <unordered_map>

#include "sdl2core.hpp"

namespace engine {

    class Keyboard {
        public:
            Keyboard();
            ~Keyboard();

            void setKeys( SDL_Event* key );
            bool isKeyDown( std::string key );
            bool isKeyUp( std::string key );
            void clearKeyboard();

        private:
            void create_keyboard_mapping();
            std::list <Uint8> keycode_down;
            std::list <Uint8> keycode_up;
            Uint8 aux;
            std::unordered_map<std::string, int> m_buttons;

    };

}

#endif
