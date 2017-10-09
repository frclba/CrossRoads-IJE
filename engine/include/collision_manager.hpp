/**
    \file collision_manager.hpp
    This file declares the CollisionManager class
*/
#ifndef COLLISION_MANAGER_HPP_
#define COLLISION_MANAGER_HPP_

#include <iostream>
#include <list>
#include <iterator>

#include "sdl2core.hpp"
#include "gameobject.hpp"

namespace engine {

    /// Class to control object collisions
    /**
        \class CollisionManager
        This class is responsible for managing collision of objects in the game   
    */
    class CollisionManager {

    public:
        CollisionManager();
        ~CollisionManager();
      
        void getCollisions( std::list <GameObject*> *objects );

        GameObject* checkCollision( GameObject* game_object, std::string type );

    private:
        bool collide( GameObject* object_1, GameObject* object_2 );

        std::list <GameObject*>* collision_list;

        /* 
            A structure that will contains the area of rectangle_1,
            with the origin at the upper left.
        */
        SDL_Rect rectangle_1;

        /* 
            A structure that will contains the are of rectangle_2,
            with the origin at the upper left.
        */
        SDL_Rect rectangle_2;

        // The result of the collision of the rectangle_1 and the rectangle_2
        SDL_Rect result;

    };

}

#endif  // COLLISION_MANAGER_HPP_
