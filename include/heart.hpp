/**
    \file heart.hpp
    This file declares the Heart class
*/
#ifndef _HEART_H_
#define _HERAT_H_

#include <iostream>
#include "game.hpp"
#include "components/component.hpp"
#include "player.hpp"

using namespace engine;

/**
    \class Heart
    This class is responsible for showing player's life
*/
class Heart : public Component {

    public:
        Heart(GameObject &main_game_object, std::string id, Player *player,
            int life) :
            Component(main_game_object, id), m_player(player), m_life(life) {}

        ~Heart();

        void update();

    private:

        bool init();

        /**
          Player to whom the life belongs
        */
        Player *m_player = NULL;

        /**
          Minimum limit to mantain life enable
          \This value is a constant and directly interferes with the level of
          difficulty of the game.
        */
        int m_life = 5;

};

#endif // _HEART_H_
