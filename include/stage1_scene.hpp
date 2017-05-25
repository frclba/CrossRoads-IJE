#ifndef __STAGE1_H__
#define __STAGE1_H__

#include <scene.hpp>
#include "components/animation.hpp"
#include "components/animation_controller.hpp"

using namespace engine;

class Stage1Scene : public Scene{
    public:

    Stage1Scene(std::string name):
	  Scene(name), jumptime(0), walkR(false), walkL(false), jump(false), attack(false), damageBool(false){}


    ~Stage1Scene();

    void setup();
    void game_logic();
    void damage_player(GameObject *player);
    void attack_player(GameObject *player);
    void move_player(GameObject *player);
    void jump_player(GameObject *player);


  void processPos(GameObject *player);
  void gravityF(GameObject *player);
  void monsterAI(GameObject *obj);

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
};

#endif
