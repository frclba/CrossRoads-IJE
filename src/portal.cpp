#include <portal.hpp>

Portal::~Portal(){}

bool Portal::init() {

    /*
        _main_game_object->main_positionX = 00;
        _main_game_object->main_positionY = 00;
    */

    interator = 0;
    timestep = 0;
    monster_number = 0;

    return true;

}

void Portal::update() {

    if( timestep < Game::instance.timer->getTicks() &&
        m_monsters[interator]->state() == GameObject::State::disabled &&
        _main_game_object->main_positionX > 0 && 
        _main_game_object->main_positionX + _main_game_object->main_width < 800
      ) {

        m_monsters[interator]->main_positionX = _main_game_object->main_positionX;
        m_monsters[interator]->main_positionY = _main_game_object->main_positionY;
        m_monsters[interator]->setState(GameObject::State::enabled);

        monster_number++;
        
        timestep = Game::instance.timer->getTicks() + 3000;
    }

    interator = (interator + 1) % m_monsters.size();

    if( monster_number <= 5 && m_background->imagePart->x == 0 ) {
        m_portal_pos->m_init_posX = 650;
    }

    if( monster_number < 10 && monster_number > 5 ) {
        m_portal_pos->m_init_posX = 1200;
    }

    if( monster_number < 20 && monster_number > 10 ) {
        m_portal_pos->m_init_posX = 1600;
    }

    if( monster_number > 20 ) {
        _main_game_object->setState(GameObject::State::disabled);
    }

}

//so chamar na main

void Portal::add_monster( GameObject* monster ){
    
    monster->setState( GameObject::State::disabled );
    m_monsters.push_back( monster );
    
}
