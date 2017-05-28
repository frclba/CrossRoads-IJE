#include "collision_manager.hpp"
#include "game.hpp"

using namespace engine;

CollisionManager::CollisionManager(){}
CollisionManager::~CollisionManager(){}

void CollisionManager::getCollisions(std::list <GameObject*> *objects){
  collision_list = objects;
}

GameObject* CollisionManager::checkCollision(GameObject* game_object,std::string type){
  for (std::list<GameObject*>::iterator obj = collision_list->begin(); obj != collision_list->end(); ++obj){
    if((*obj)->type == type && collide(game_object,*obj)){
      return (*obj);
    }
  }
  return NULL;
}

bool CollisionManager::collide(GameObject* obj1, GameObject* obj2){
  rect1.x = obj1->main_positionX; 
  rect1.y = obj1->main_positionY;
  rect1.h = obj1->main_height;
  rect1.w = obj1->main_width;
  rect2.x = obj2->main_positionX;
  rect2.y = obj2->main_positionY;
  rect2.h = obj2->main_height;
  rect2.w = obj2->main_width;

  return SDL_IntersectRect(&rect1, &rect2, &result);
}
