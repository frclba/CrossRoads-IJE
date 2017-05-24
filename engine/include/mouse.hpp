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

            //funcao para pegar posicao do mouse.
            void set_position();
            //funcao para verificar se omause esta em cima de uma gameobject
            bool is_over(GameObject *gameObject);
            bool is_right_button();
            bool is_left_button();

            //posicao do mause
            int mouseX;
            int mouseY;

        private:

    };
}

#endif
