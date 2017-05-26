#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include<iostream>
#include "components/component.hpp"
#include "components/animation_controller.hpp"

using namespace engine;

class MonsterAI : public Component{

public:
  MonsterAI(GameObject &_main_game_object, std::string component_id, GameObject *player, AnimationControllerComponent *monster_controler):
    Component(_main_game_object,component_id), m_player(player), m_monster_controler(monster_controler),dy(0){}
  ~MonsterAI();

  bool init();
  void update();

private:
  void gravityF();
  void processPos();


  float monster_move = 4;
  const int ground = 552;
  const int gravity = 1;
  const float jumpF = 2;
  float dy;
  
  GameObject* m_player;
  AnimationControllerComponent* m_monster_controler;
  
};


#endif
  
