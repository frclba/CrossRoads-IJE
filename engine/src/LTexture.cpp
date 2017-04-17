#include<iostream>
#include "../include/LTexture.h"
using namespace std;

LTexture::LTexture(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    resizeValue = 1;
}

LTexture::~LTexture(){
    free();
}

bool LTexture::loadFromFile(std::string path,SDL_Renderer* gRenderer){
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == NULL){
        Log::instance.error("ERRO to find " + path);
        return false;
    }
    else{
        SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0,0xFF,0xFF));
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ){
            Log::instance.error("Unable to create texture from: " + path + ". SDL Error: " + SDL_GetError());
        }
        else{
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );

    }

    mTexture = newTexture;
    return mTexture != NULL;

}

void LTexture::free(){
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
void  LTexture::render( int x, int y,SDL_Renderer* gRenderer,SDL_Rect* clip){
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    if (clip != NULL) {
        renderQuad.w = clip->w ;//* resizeValue;
        renderQuad.h = clip->h ;//* resizeValue;
    }
    cout << resizeValue;
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

void LTexture::resize(int resizeValue){
    this->resizeValue = resizeValue;
}

int LTexture::getWidth(){
    return mWidth;
}

int LTexture::getHeight(){
    return mHeight;
}
