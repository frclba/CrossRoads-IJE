/**
    \file animation_controller.cpp
    AnimationControllerComponent implementation
*/

#include "components/animation_controller.hpp"
#include "game.hpp"

using namespace engine;

/**
     This method disabled all animations and enable current animation to startup
     \return true value if active animation
*/
bool AnimationControllerComponent::init() {

    for( auto id_animation: m_animations_map ) {
        if( current_animation != id_animation.first ) {
            id_animation.second->disable();
        }
        else {
            id_animation.second->enable();
        }
    }

    return true;

}

/**
    This method closes the AnimationControllerComponent in the game
    \return true value to disabled the component
*/
bool AnimationControllerComponent::shutdown() {

    return true;

}

/**
    Method responsible for making the exchange between animations when the current animation ends the execution
*/
void AnimationControllerComponent::update() {

    if( current_animation == "" ) {
        Log::instance.warning("No animations to play!");
    }
    else {
        auto animation = m_animations_map[current_animation];

        if( next_animation != "" && animation->has_finished() ) {
	        change_animations();
        }
    }

}

/**
    Adds a new animation to the running queue of animations
    \param name
    \param animation referencess address to new animation
*/
void AnimationControllerComponent::add_animation(std::string name,
                                                 Animation & animation) {

    if( m_animations_map.find(name) != m_animations_map.end() ) {
        Log::instance.warning("Animation " + name + " already exists!");
        return;
    }

    m_animations_map[name] = &animation;

    if( m_animations_map.size() == 1 ) {
        current_animation = name;
    }

}

/**
    Execute animation
    \param[in] name
    \param[in] wait_to_finish
    \parblock
        true if should be wait curretent animation finished
        false if shloudn't be wait current animation finished
    \endparblock
*/
void AnimationControllerComponent::play_animation(std::string name,
                                                  bool wait_to_finish) {

    next_animation = name;
    m_animations_map[current_animation]->flipping(flip);

    if( !wait_to_finish ) {
        change_animations();
    }

}

/**
    Change the current animation to the next one in the list
*/
void AnimationControllerComponent::change_animations() {

    auto animation = m_animations_map[current_animation];
    animation->disable();

    current_animation = next_animation;

    next_animation = "";

    animation = m_animations_map[current_animation];
    animation->enable();
    animation->setup();

}

/**
    Set filp side
    \param isFlip side value
    \parblock
        true if RIGHT
        false if LEFT
    \endparblock
*/
void AnimationControllerComponent::flipping(bool isFlip) {

    flip = isFlip;

}
