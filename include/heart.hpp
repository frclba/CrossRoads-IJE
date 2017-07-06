#ifndef _HEART_HPP_
#define _HERAT_HPP_

#include<iostream>
#include "game.hpp"
#include "components/component.hpp"
#include "player.hpp"

using namespace engine;

class Heart : public Component{

public:
  Heart(GameObject &main_game_object, std::string id,Player* player,int life):
    Component(main_game_object, id), m_player(player), m_life(life){}

    ~Heart();

    bool init();
    void update();

private:
  Player *m_player;
  int m_life;

};

#endif
