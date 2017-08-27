#include"bossAI.hpp"

bool Boss::init() {

    life = 10;
    timestep = 0;
    move_time = 0;
    fireball_time = 0;
    side = false;

    return true;

}

void Boss::update() {

    m_boss_animation->play_animation("boss_idle", true);

    if( _main_game_object->main_positionX > -10 &&
        _main_game_object->main_positionX +
        _main_game_object->main_width < 850 ) {

        if ( fireball_attack ) {

            // fireball_controller();

        }
        else if( dash_attack ) {
            boss_move();
        }

        m_boss_animation->flipping(!side);

        if( timestep < Game::instance.timer->getTicks() ) {

            if( m_player->main_positionY > 300 ) {
                dash_attack = true;
                fireball_attack = false;
                m_fireball->setState(GameObject::State::disabled);
            }
            else {
                dash_attack = false;
                fireball_attack = true;
                m_boss_animation->play_animation("boss_howl");
                m_fireball->setState(GameObject::State::enabled);
            }

            timestep = Game::instance.timer->getTicks() + 3000;
        }

            boss_damage();
    }

}

void Boss::boss_damage() {

    AudioComponent* boss_full_putasso_audio = (dynamic_cast<AudioComponent*> (
                                               _main_game_object->get_component(
                                               "boss_full_putasso_audio")));

    if( Game::instance.collision_manager->checkCollision(
        _main_game_object, "attack_box") ||
        Game::instance.collision_manager->checkCollision(
        _main_game_object, "bullet") ) {

        if( time_damage < Game::instance.timer->getTicks() ) {
            life--;
            time_damage = Game::instance.timer->getTicks() + 1000;
        }

        if( life == 3 ) {
            boss_full_putasso_audio->play(0, -1);
        }

        if( life <= 0 ) {
            Game::instance.change_scene("Win Scene");
        }
    }

}

void Boss::boss_move() {

    AudioComponent* boss_dash_audio = (dynamic_cast<AudioComponent*> (
                                       _main_game_object->get_component(
                                       "boss_dash_audio")));

    boss_dash_audio->play(0, -1);

    m_boss_animation->play_animation("boss_dash", true);

    if( move_time < Game::instance.timer->getTicks() ) {
        // side = !side;
        move_time = Game::instance.timer->getTicks() + 900;
    }

    if( side ) {
        m_position->m_init_posX -=10;
    }
    else {
      m_position->m_init_posX +=10;
    }

    if( _main_game_object->main_positionX <=10 && side ) {
        side = !side;
        dash_attack = false;
    }
    if( _main_game_object->main_positionX +
        _main_game_object->main_width >= 800 && !side ) {
        side = !side;
        dash_attack = false;
    }

}

Boss::~Boss() {}
