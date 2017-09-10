/**
    \file cameraposition.hpp
    This file declares the CameraPosition class
*/
#ifndef _CAMERA_POSITION_HPP_
#define _CAMERA_POSITION_HPP_

#include <iostream>

#include "game.hpp"
#include "components/component.hpp"
#include "components/image.hpp"

using namespace engine;

/**
    \class CameraPosition
    This class is responsible for the movement of the background scenario
*/
class CameraPosition : public Component{

public:
    CameraPosition( GameObject &main_game_object, std::string id,
                    ImageComponent *background, int init_posX, int init_posY):
        Component(main_game_object, id), m_init_posX(init_posX), m_init_posY(init_posY), m_background(background){}
        ~CameraPosition();

        bool init();

        void update();

        int m_init_posX;
        int m_init_posY;

private:
  ImageComponent *m_background;
};

#endif  // _CAMERA_POSITION_HPP_
