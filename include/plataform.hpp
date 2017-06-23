#ifndef _PLATAFORM_HPP_
#define _PLATAFORM_HPP_
#include <iostream>

#include "game.hpp"
#include "components/component.hpp"
#include "components/image.hpp"

using namespace engine;

class Plataform : public Component{

public:
  Plataform(GameObject &main_game_object, std::string id,ImageComponent *background,int init_posX,int init_posY):
    Component(main_game_object, id),m_background(background),m_init_posX(init_posX),m_init_posY(init_posY){}
    ~Plataform();

    bool init();
    void update();


private:
  int m_init_posX;
  int m_init_posY;
  ImageComponent *m_background;
};

#endif
