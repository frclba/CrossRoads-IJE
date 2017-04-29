#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include<iostream>
#include "sdl2core.hpp"
#include "gameobject.hpp"

namespace engine{
    class Mouse {

        public:

            Mouse():mouseX(0),mouseY(0){};
            ~Mouse();

            void set_position();
            bool is_over(GameObject *gameObject);
            int mouseX;
            int mouseY;

        private:

    };
}

#endif
