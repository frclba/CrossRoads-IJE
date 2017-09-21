/**
    \file cameraposition.cpp
    This file implements the CameraPosition class
*/
#include "cameraposition.hpp"

CameraPosition::~CameraPosition(){}

/**
    This method defines an initial position for the background image
    \return return a true value that make the cameraposition active
*/
bool CameraPosition::init() {

    _main_game_object->main_positionX = m_init_posX;
    _main_game_object->main_positionY = m_init_posY;

    return true;

}

/**
    This method updates the position for the background image
*/
void CameraPosition::update() {

    _main_game_object->main_positionY = m_init_posY;
    _main_game_object->main_positionX = m_init_posX - m_background->imagePart->x;

}
