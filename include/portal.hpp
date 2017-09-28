/**
    \file porta.hpp
    This file declares the porta class
*/
#ifndef _PORTAL_HPP_
#define _PORTAL_HPP_

#include <iostream>
#include <vector>

#include "game.hpp"
#include "gameobject.hpp"
#include "components/component.hpp"
#include "components/image.hpp"
#include "cameraposition.hpp"

using namespace engine;


/**
    \class portal
    This class is responsible for create a portal for monsters appear in the game
*/

class Portal : public Component{

public:
    Portal( GameObject &main_game_object, std::string id, 
            ImageComponent *background, CameraPosition *portal_pos):
        
        Component( main_game_object, id), 
        interator( 0 ), 
        m_background( background ), 
        m_portal_pos( portal_pos ){}
        ~Portal();

        bool init();
    
        void update();
        void add_monster(GameObject* monster);

private:
    std::vector <GameObject*> m_monsters;

    unsigned int timestep = 0;
    unsigned int interator = 0;
    unsigned int monster_number = 0;

    ImageComponent *m_background = NULL;
    CameraPosition *m_portal_pos = NULL;
  
};

#endif  // _PORTAL_HPP_