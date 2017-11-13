/**
    \file collision_manager.cpp
    This file declares the CollisionManager class
*/
#include "collision_manager.hpp"
#include "game.hpp"
#include <assert.h>

using namespace engine;

CollisionManager::CollisionManager(){}
CollisionManager::~CollisionManager(){}

/**
    This method is responsible for getting collisions from the game objects
    \param *objects
    \parblock
        Is a input parameter that represents objects of the game(!=NULL)
    \endparblock
*/
void CollisionManager::getCollisions( std::list <GameObject*> *objects ) {

    collision_list = objects;

    if (objects == NULL) {
        Log::instance.error("The getCollisions method is recieving a NULL list of objects");
    }
    else {
        // Do nothing
    }

    assert( collision_list != NULL );

}

GameObject* CollisionManager::checkCollision( GameObject* game_object,
                                              std::string type ) {
    if (collision_list == NULL) {
        Log::instance.error("The list of objects to colide is NULL");
    }
    else {
        // Do nothing
    }

    assert( collision_list != NULL);

    for (std::list<GameObject*>::iterator obj = collision_list->begin();
         obj != collision_list->end(); ++obj){
        if( ( *obj )->type == type && collide( game_object, *obj ) ) {
            return (*obj);
        }
    }

    return NULL;

}

/**
    This method is responsible for colliding objects and repositioning them
    \param object_1, object_2
    \parblock
        Is a input parameter that represents objects of the game(!=NULL)
    \endparblock
    \return return a true value to result of objects intersection
*/
bool CollisionManager::collide( GameObject* object_1, GameObject* object_2 ) {

    if (object_1 == NULL || object_2 == NULL) {
        Log::instance.error("One or both of the objects colliding are NULL");
        return false;
    }
    else {
        rectangle_1.x = object_1->main_positionX;
        rectangle_1.y = object_1->main_positionY;
        rectangle_1.h = object_1->main_height;
        rectangle_1.w = object_1->main_width;
        rectangle_2.x = object_2->main_positionX;
        rectangle_2.y = object_2->main_positionY;
        rectangle_2.h = object_2->main_height;
        rectangle_2.w = object_2->main_width;

        return SDL_IntersectRect(&rectangle_1, &rectangle_2, &result);
    }
}
