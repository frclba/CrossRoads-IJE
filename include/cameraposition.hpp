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
class CameraPosition : public Component {

public:
    CameraPosition( GameObject &main_game_object, std::string id,
                    ImageComponent *background,
                    int horizontal_starting_position,
                    int vertical_starting_position) :
                    Component(main_game_object, id),
                    m_horizontal_starting_position(
                        horizontal_starting_position),
                    m_vertical_starting_position(vertical_starting_position),
                    m_background(background) {}

        ~CameraPosition();

        bool init();

        void update();

        int m_horizontal_starting_position = 0;
        int m_vertical_starting_position = 0;

private:
  ImageComponent *m_background = NULL;
};

#endif  // _CAMERA_POSITION_HPP_
