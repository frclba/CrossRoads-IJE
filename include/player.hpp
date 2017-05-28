#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__
#include <iostream>

#include "components/component.hpp"
#include "components/animation_controller.hpp"
#include "game.hpp"

using namespace engine;

class Player : public Component{
    public:

    Player(GameObject &_main_game_object, std::string component_id, AnimationControllerComponent *animC):
      Component(_main_game_object,component_id), animCtrl(animC),
      walkR(false), walkL(false), jump(false), stand(false), attack(false), damageBool(false){}


  

    ~Player();

    bool init();
    void update();
  
    void damage_player();
    void attack_player();
    void move_player();
    void jump_player();


  void processPos();
  void gravityF();
  bool has_ground();
  //void monsterAI(GameObject *obj);

    GameObject *player;
    GameObject *plataform;
    GameObject *monster;

    private:
        unsigned int jumptime;
        bool walkR;
        bool walkL;
        bool jump;
        bool stand;
        bool attack;
        bool damageBool;
        AnimationControllerComponent *animCtrl;
        AnimationControllerComponent *monster_controler;
        GameObject *ground;


        float dy;
};

#endif
