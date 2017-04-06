#include <iostream>
#include <vector>
#include "Sprite.h"

using namespace engine;
using namespace std;

Sprite::Sprite(){
    texture = NULL;
    texture = new LTexture();
}
Sprite::~Sprite(){
    delete texture;
}

bool Sprite::loadMedia(int widthDiv,int heightDiv,string localIMG, SDL_Renderer* render){
    bool success = true;
    m_widthDiv = widthDiv;
    m_heightDiv = heightDiv;

    success = (texture->loadFromFile(localIMG, render));
    if(!success){
        cout << "ERRO to open " + localIMG << endl;
    }
    else{
        //ler matriz de imagems em um arquivo
        for (int h = 0; h < texture->getHeight(); h += heightDiv) {
            for(int w = 0; w < texture->getWidth() ; w += widthDiv){
                SDL_Rect *rect = new SDL_Rect();

                rect->x = w;
                rect->y = h;
                rect->w = widthDiv;
                rect->h = heightDiv;

                spritesClips.push_back(rect);
            }
        }
    }



    return success;
}

void Sprite::showImage(int x, int y, SDL_Renderer *render,int numIMG){
    // SDL_Delay(100);
    texture->render(x,y,render,spritesClips[numIMG]);

}
