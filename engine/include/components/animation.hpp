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

            Animation(GameObject &main_game_object,std::string id ,std::string path,unsigned int widthDiv,unsigned int heightDiv,int num_image):
                ImageComponent(main_game_object, id,path) ,m_widthDiv(widthDiv),m_heightDiv(heightDiv),m_num_image(num_image),
                main_frame(0),delay(0), timestep(0){}

            ~Animation();

            bool init();
            void draw();

            void setAnimation(std::string name,int begin, int end);

            bool useAnimation(std::string name);

            void setDelay(int delay);

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
