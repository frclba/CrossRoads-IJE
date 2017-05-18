#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <iostream>
#include <vector>

#include "sdl2core.hpp"
#include "components/image.hpp"
#include "game.hpp"
#include "Timer.hpp"

#include <unordered_map>
#include <vector>

namespace engine{
    class Animation : public ImageComponent {
        public:

        //construtor animation
        //  param:
        //    main_game_object = referencia do objetoque a animation pertence.
        //    std::string id = identidade do component.
        //    widthDiv = valor de largura que ira dividir a imagem.
        //    heightDiv = valor de altura que sera dividida a imagem.
        //    num_image = numero de sprites contida na imagem
            Animation(GameObject &main_game_object, std::string id, std::string path, unsigned int widthDiv, unsigned int heightDiv, int num_image):
                ImageComponent(main_game_object, id, path), m_widthDiv(widthDiv),
                m_heightDiv(heightDiv), m_num_image(num_image),
                main_frame(0),delay(0), timestep(0){}

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

            void flipping(bool isFlip);

            bool has_finished();

            void setup();

            SDL_RendererFlip flip = SDL_FLIP_NONE;
        private:

            const int BEGIN = 0;
            const int END = 1 ;

            unsigned int m_widthDiv;
            unsigned int m_heightDiv;

            std::vector<SDL_Rect*> imageVector;

            int main_animation[2];

            std::unordered_map <std::string, int [2]> animationMap;

            int m_num_image;

            int main_frame;

            int delay;

            int timestep;

    };
}
#endif
