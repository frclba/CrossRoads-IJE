#ifndef LTEXTURE_H
#define LTEXTURE_H

#include<iostream>
#include "sdl2core.hpp"

class LTexture
{
public:

    //Construtor
    LTexture();

    //Destrutor
    ~LTexture();

    //Carrega imagem 
    //param:
    //  path = caminho onde a imagem se localiza.
    //  gRenderer = SDL_Renderer usado.
    bool loadFromFile( std::string path,SDL_Renderer *gRenderer );

    //Libera memoria da imagem
    void free();

    //Mostra imagem na tela.
    //param:
    //  x = posicao no eixo x onde a imagem vai aparecer
    //  y = posicao no eixo y onde a imagem vai aparecer
    //  render = SDL_Renderer
    //  clip = mostra apenas determinado pedaço da imagem(ultilizado na função sprite)
    void render( int x, int y, SDL_Renderer* , SDL_Rect* clip = NULL);

    //Retorna largura da imagem
    int getWidth();

    //Retorna altura da imagem
    int getHeight();

    //Metodo ultilizado pra mudar tamanho dos rects que vem no parametro da sprites
    void resizeRect(int resizeValue);

private:
    SDL_Texture* mTexture;
    //largura da imagem
    int mWidth;
    //altura da imagem
    int mHeight;
    //variavel para mudar tamanho da divisão rect
    int resizeValue;
};

#endif
