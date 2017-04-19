#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "sdl2core.hpp"

// namespace engine{
    enum keycode{
        KEY_UNKNOWN,
        KEY_DEFAULT,

        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,

        KEY_RETURN,
        KEY_SPACE,
        KEY_BACKSPACE,
        KEY_TOTAL
    };

    class Keyboard {
    public:
        static bool isKeyDown(keycode key);
    private:
        static const Uint8 *Keyboard_State;
    };
// }

#endif
