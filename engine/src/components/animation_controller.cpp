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

  if(code == EMPTY_STRING){
      Log::instance.error("can not change animation, if next_animation is empty, method:" + method);
      exit(0);
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

    if( current_animation == NO_ANIMATION ) {
        Log::instance.warning("No animations to play!");
    }
    else {
        auto animation = m_animations_map[current_animation];

        if( next_animation != NO_ANIMATION && animation->has_finished() ) {
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


    Animation *validates;
    validates = &animation;

    if(name != "" && validates){
      if( m_animations_map.find(name) != m_animations_map.end() ) {
          Log::instance.warning("Animation " + name + " already exists!");
      }
      else{

          // Default else.

      }

      m_animations_map[name] = &animation;

      if( m_animations_map.size() == HAVE_ANIMATION ) {
          current_animation = name;
      }
      else{

          // Default else.

      }
      return SUCCESS;

    }
    else if(!validates){
      return NULL_OBJECT;
    }
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
    else{
      return EMPTY_STRING;
    }

}

/**
    Change the current animation to the next one in the list
*/
int AnimationControllerComponent::change_animations() {

    if(next_animation != ""){
        auto animation = m_animations_map[current_animation];
        animation->disable();

        current_animation = next_animation;

        next_animation = "";

        animation = m_animations_map[current_animation];
        animation->enable();
        animation->setup();
        return SUCCESS;
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
