#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include<iostream>
#include<list>
#include <algorithm>

#include "sdl2core.hpp"

namespace engine{
    class Keyboard {
        public:
            Keyboard();
            ~Keyboard();
            
            void setKeys(SDL_Event* key);
            bool isKeyDown(Uint8 key);
            bool isKeyUp(Uint8 key);
            void clearKeyboard();
        private:
            std::list <Uint8> keycode_down;
            std::list <Uint8> keycode_up;
            static const Uint8 *Keyboard_State;
    };
}

#endif
