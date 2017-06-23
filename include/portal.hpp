#ifndef _PORTAL_HPP_
#define _PORTAL_HPP_
#include <iostream>
#include <vector>

#include "game.hpp"
#include "gameobject.hpp"
#include "components/component.hpp"
#include "components/image.hpp"

using namespace engine;

class Portal : public Component{

public:
  Portal(GameObject &main_game_object, std::string id,ImageComponent *background):
    Component(main_game_object, id),interator(0), m_background(background){}
    ~Portal();

    bool init();
    void update();

    void add_monster(GameObject* monster);

private:
  std::vector <GameObject*> m_monsters;
  unsigned int timestep;
  unsigned int interator;
  unsigned int monster_number;
  ImageComponent *m_background;
  
  
  
};

#endif
