#ifndef SPRITE_H
#define SPRITE_H

#include<iostream>
#include <vector>

#include "sdl2core.hpp"

#include "LTexture.h"

class Sprite{

public:
    Sprite();

    ~Sprite();

    bool loadMedia(int widthDiv,int heightDiv,std::string localIMG, SDL_Renderer* render);

    void showImage(int x, int y, SDL_Renderer* render ,int numIMG);

    LTexture *texture;
    std::vector <SDL_Rect*> spritesClips;

private:
    int widthDiv;
    int heightDiv;


};



#endif
