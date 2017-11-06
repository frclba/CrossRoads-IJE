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

    if( current_animation == NO_ANIMATION ) {
        Log::instance.warning("No animations to play!");
    }
    else {
        auto actual_animation = m_animations_map[current_animation];

        if( next_animation != NO_ANIMATION && actual_animation->has_finished() ) {
	        change_animations();
        }
    }

}

/**
    Adds a new animation to the running queue of animations
    \param name
    \param animation referencess address to new animation
*/
void AnimationControllerComponent::add_animation(std::string name_animation,
                                                 Animation & actual_animation) {

    if( m_animations_map.find(name_animation) != m_animations_map.end() ) {
        Log::instance.warning("Animation " + name_animation + " already exists!");
    }
    else{
        // Default else.
    }

    m_animations_map[name_animation] = &actual_animation;

    if( m_animations_map.size() == HAVE_ANIMATION ) {
        current_animation = name_animation;
    }
    else{
        // Default else.
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
void AnimationControllerComponent::play_animation(std::string name_animation,
                                                  bool wait_to_finish) {

    if (!name.empty()) {
        next_animation = name;
    }
    else {
        Log::instance.error("The name of the animation is empty");
        next_animation = current_animation;
    }

    m_animations_map[current_animation]->flipping(flip);

    if( !wait_to_finish ) {
        change_animations();
    }
    else{

        // Default else.

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
    \param is_flip side value
    \parblock
        true if RIGHT
        false if LEFT
    \endparblock
*/
void AnimationControllerComponent::flipping(bool is_flip) {

    flip = is_flip;

}
