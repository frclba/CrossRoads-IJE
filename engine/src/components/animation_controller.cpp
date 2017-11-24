/**
    \file animation_controller.cpp
    AnimationControllerComponent implementation
*/

#include "components/animation_controller.hpp"
#include "game.hpp"

using namespace engine;

const int EMPTY_STRING = -2;
const int NULL_OBJECT = -3;
const int SUCCESS = 1;

void valid_change_animations(int code, std::string method){

  // validades if the name of animation is empty to treat this exception.
  if(code == EMPTY_STRING){
      Log::instance.error("can not change animation, if next_animation is empty, method:" + method);
      exit(0);
  // validades if change_animation returns 1 = success to treat with log
  }else if(code == SUCCESS){
      Log::instance.info("animation changed");
  }

}


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

    // Verify if  current animation is a empty string to treat with warning.
    if( current_animation == NO_ANIMATION ) {
        Log::instance.warning("No animations to play!");
    }
    else {
        auto actual_animation = m_animations_map[current_animation];

        // Verify if next animation is not a empty string and actual animation
        // finished to change animation.
        if( next_animation != NO_ANIMATION && actual_animation->has_finished() ) {
	        valid_change_animations(change_animations(), "AnimationControllerComponent::update");
        }
    }

}

/**
    Adds a new animation to the running queue of animations
    \param name
    \param animation referencess address to new animation
*/
int AnimationControllerComponent::add_animation(std::string name,
                                                 Animation & animation) {

    assert(name != "");

    Animation *validates;
    validates = &animation;

    // Validades if animation is NULL or name is empty, to point a int to treat properly
    if(name != "" && validates){
      // Verifies the existence of animation on animations map through the name.
      if( m_animations_map.find(name) != m_animations_map.end() ) {
          Log::instance.warning("Animation " + name + " already exists!");
      }
      else{
          // Default else.
      }

      m_animations_map[name] = &animation;

      // Verifies the animations map size to set a current animation.
      if( m_animations_map.size() == HAVE_ANIMATION ) {
          current_animation = name;
      }
      else{

          // Default else.

      }
      return SUCCESS;

    }
    // return -3 to point that need a treatment for null object
    else if(!validates){
      return NULL_OBJECT;
    }
    // return -2 to point that need a treatment for empty string
    else{
      return EMPTY_STRING;
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
int AnimationControllerComponent::play_animation(std::string name,
                                                 bool wait_to_finish) {

    assert(name != "");

    // Validates if animations name is empty, to point a int to treat properly
    if( name != "" ){
      next_animation = name;
      m_animations_map[current_animation]->flipping(flip);

      if( !wait_to_finish ) {
          valid_change_animations(change_animations(), "AnimationControllerComponent::play_animation");
      }
      else{

          // Default else.

      }
      return SUCCESS;
    }
    // return -2 to point that need a treatment for empty string
    else{
      return EMPTY_STRING;
    }

}

/**
    Change the current animation to the next one in the list
*/
int AnimationControllerComponent::change_animations() {

    // Validates if next animation name is empty, to point a int to treat properly
    if(next_animation != ""){
        auto animation = m_animations_map[current_animation];
        animation->disable();

        current_animation = next_animation;

        next_animation = "";

        animation = m_animations_map[current_animation];
        animation->enable();
        animation->setup();
        return SUCCESS;
        
    // return -2 to point that need a treatment for empty string
    }else{
        return EMPTY_STRING;
    }

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
