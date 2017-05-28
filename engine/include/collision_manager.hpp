#ifndef COLLISION_MANAGER_HPP_
#define COLLISION_MANAGER_HPP_

#include <iostream>
#include <list>
#include <iterator>


#include "sdl2core.hpp"
#include "gameobject.hpp"

namespace engine{
  class CollisionManager{
  public:

    CollisionManager();
    
    ~CollisionManager();
    
    void getCollisions(std::list <GameObject*> *objects);
    GameObject* checkCollision(GameObject* game_object,std::string type);
  private:

    bool collide(GameObject* obj1, GameObject* obj2);
    std::list <GameObject*>* collision_list;

    SDL_Rect rect1;
    SDL_Rect rect2;
    SDL_Rect result;



  };
}
#endif
