#ifndef SPRITE_H
#define SPRITE_H

#include<iostream>
#include <vector>

#include "sdl2core.hpp"
#include "LTexture.h"

namespace engine{

    class Sprite{
        public:
            Sprite();

            ~Sprite();

            bool loadMedia(int widthDiv,int heightDiv,std::string localIMG, SDL_Renderer* render);

            void showImage(int x, int y, SDL_Renderer* render ,int numIMG);

            LTexture *texture;
            std::vector <SDL_Rect*> spritesClips;

            void resize(int resizeValue);

        private:
            float m_widthDiv;
            float m_heightDiv;

    };

}

#endif
