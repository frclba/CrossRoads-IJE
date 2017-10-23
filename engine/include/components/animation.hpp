/**
    \file animation.hpp
    This file contains header declaretion for Animation class
*/

#ifndef ANIMATION_H_
#define ANIMATION_H_

#define PATH_ERROR ""

#include <iostream>
#include <vector>
#include <unordered_map>
#include "sdl2core.hpp"
#include "components/image.hpp"
#include "game.hpp"
#include "Timer.hpp"


namespace engine{

    /// Class responsible for rendering an animated image
    /**
        \class Animation
        Class responsible for picking up an image(png) and building the
        animation related to that image.
    */
    class Animation : public ImageComponent {

        public:
            //construtor animation
            //  param:
            //    main_game_object = referencia do objetoque a animation pertence.
            //    std::string id = identidade do component.
            //    width_division = valor de largura que ira dividir a imagem.
            //    height_division = valor de altura que sera dividida a imagem.
            //    num_image = numero de sprites contida na imagem
            Animation(GameObject &main_game_object, std::string id,
                      std::string path, unsigned int width_division,
                      unsigned int height_division, int num_image) :
                      ImageComponent(main_game_object, id, path),
                      m_width_division(width_division),
                      m_height_division(height_division),
                      m_num_image(num_image),
                      main_frame(0),delay(0),
                      time_step(0){
                        
                // Default function call.
                        
            }

            //destrutor
            ~Animation();

            //funcao init da animation
            bool init();

            //funcao draw da animation
            void draw();

            //setAnimation = funcao para cadastrar um trexo de animacao da imagem
            //  EX: suponha que a imagems de andar do personagem esteja na figura 1 2 3 e a de pular
            //         esteja na 4 e 5 a função deve ser declarada
            //         setAnimation("andar",1,3);
            //         setAnimation("pular",4,5);
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
            void setAnimation(std::string name,int begin, int end);


            //useAnimation = usa a animacao cadastrada pelo set animation
            //param:
            //  name = nome cadastrado no setAnimation.
            bool useAnimation(std::string name);

            //setDelat = seleciona o delay em ms que a animacao da ao passar de imagem
            void setDelay(int delay);

            void flipping(bool is_flip);

            bool has_finished();

            void setup();

            /** 
                Control flip state rendering of character, monsters and boss.
            */
            SDL_RendererFlip flip = SDL_FLIP_NONE;

        private:
            /** 
                Initialize and finish game animations.
            */
            const int BEGIN = 0;
            const int END = 1 ;

            /** 
                Control animations sizes.
            */
            unsigned int m_width_division = 0;
            unsigned int m_height_division = 0;

            /** 
                Determine image in a vector.
            */
            std::vector<SDL_Rect*> image_vector;

            /** 
                Control game animation.  
            */
            int main_animation[2] = {0};

            /** 
                Determine map animations in 2D. 
            */
            std::unordered_map <std::string, int [2]> animation_map;

            /** 
                Number os images in screen. 
            */
            int m_num_image = 0;

            /** 
                Control level frame. 
            */
            int main_frame = 0;

            /** 
                Control delay beetwen actions.  
            */
            int delay = 0;

            /** 
                Control time of actions in game. 
            */
            int time_step = 0;

            void build_animation(SDL_Surface *image);

    };

}

#endif // ANIMATION_H
