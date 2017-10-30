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

    /**
        Declares the contructor, defining the initial values
        of the members.
    */    
    Portal( GameObject &main_game_object, std::string id,
            ImageComponent *background, CameraPosition *portal_pos):

        Component( main_game_object, id),
        monster_number_iterator( 0 ),
        m_background( background ),
        m_portal_pos( portal_pos ){}
        ~Portal();


        void update();
        void add_monster(GameObject* monster);

private:

    bool init();

    void apparition_of_monsters();
    void horizontal_starting_position();

    std::vector <GameObject*> m_monsters;

    /**
        This attribute is responsible for the time delay between monsters birth
    */
    unsigned int time_between_monsters = 0;

    /**
        This attribute is responsible for alterning between the monsters
    */
    unsigned int monster_number_iterator = 0;

    /**
        This attribute is responsible for counting how many mosters
        has come out the portal
    */
    unsigned int monsters_out_of_portal = 0;

    ImageComponent *m_background = NULL;
    CameraPosition *m_portal_pos = NULL;

};

#endif  // _PORTAL_HPP_
