#include "heart.hpp"

Heart::~Heart() {}

bool Heart::init() {

    _main_game_object->setState(GameObject::State::enabled);
    return true;

}

void Heart::update() {

    if( m_life > m_player->life_points ) {
        _main_game_object->setState(GameObject::State::disabled);
    }

}
