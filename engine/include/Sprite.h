#ifndef SPRITE_H
#define SPRITE_H

#include<iostream>
#include <vector>

#include "sdl2core.hpp"
#include "LTexture.h"

namespace engine{

    class Sprite{
        public:
            //Construtor
            Sprite();
            
            //Destrutor
            ~Sprite();
            
            //loadMedia
            //Carrega imagem e divide seus frames.
            //@param:
            //  widthDiv = Divisao das larguras das imagems da animação 
            //      Ex: pra uma imagem co 5 figuras e 1000 delargura a entrada indicada é (1000/5);
            //  heightDiv = Divisao da altura das imagems da animação 
            //      Ex: pra uma imagem com 2 figuras e 500 de altura a entrada indicada é (500/2);
            //  localIMG = local onde a imagem se encomtra no projeto
            //  render = Passar o SDL_Renderer ultilizado.
            bool loadMedia(int widthDiv,int heightDiv,std::string localIMG, SDL_Renderer* render);
            
            //showImage
            //Mostra uma imagem expecifica do conjunto de imagens
            //x = posição no eixo x onde a imagem sera mostrada
            //y = posição no eixo y onde a imagem sera mostrada
            //render = Passar o SDL_Renderer ultilizado.
            //posicao onde a imagem se encontra 
            //  Ex:
            //
            //      |##################################################               
            //      |            |            |           |           |
            //      |     1      |     2      |     3     |     4     |
            //      |            |            |           |           |
            //      |##################################################               
            //      |            |            |           |           |
            //      |     5      |      6     |     7     |    8      |
            //      |            |            |           |           |
            //      |##################################################
            //
            //     obs: onde o numero é a posição
            //     obs2: o numero de posicoes pode variar de acordo com a divisão feita no loadMedia.
            //
            void showImage(int x, int y, SDL_Renderer* render ,int numIMG);

            //resize
            //Muda o tamanho das imagems que compoem o objeto de Sprite
            //resizeValue =  valor a ser multitiplicado pelo width e height
            //  Obs: nao deve ser 0 pois todo numero multiplicado por 0 é 0 ou seja a imagem vai desaparecer.
            void resize(int resizeValue);
            
            //Classe LTexture mais informacoes na LTexture.h
            LTexture *texture;

            //SDL_rect = contem as dimensoes das divisoes
            std::vector <SDL_Rect*> spritesClips;

        private:
            //tamanho das divisoes das imagens 
            float m_widthDiv;
            float m_heightDiv;
            //
    };

}

#endif
