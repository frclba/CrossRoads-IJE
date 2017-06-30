#ifndef __STAGE1_H__
#define __STAGE1_H__

#include <scene.hpp>
#include "components/animation.hpp"
#include "components/animation_controller.hpp"
#include "components/component.hpp"
#include "player.hpp"

using namespace engine;

class Stage1Scene : public Scene{
public:

  Stage1Scene(std::string name):
    Scene(name){}//, jumptime(0), walkR(false), walkL(false), jump(false), attack(false), damageBool(false){}


  ~Stage1Scene();


  void game_logic();
  void bullet();
private:

  GameObject* ground_stage1;
  GameObject* plataform ;
  GameObject* plataform2; 
  GameObject* plataform3; 

  GameObject* portal ;
  GameObject* background; 
  ImageComponent* back_img;
  GameObject* fire_ball ;

  GameObject *bullet1 ;
  GameObject *player ;
  Player *player_controller;

  bool bulletDir1;
  unsigned int timestep ;
  
};

#endif
