#include "components/animation_controller.hpp"
#include "game.hpp"

using namespace engine;

bool AnimationControllerComponent::init(){
    // Log::instance.info("Init AnimationControllerComponent");

    for(auto id_animation: m_animations_map) {
      if (current_animation != id_animation.first)
            id_animation.second->disable();
        else
            id_animation.second->enable();
    }

    return true;
}

bool AnimationControllerComponent::shutdown(){
    // Log::instance.info("Shutdown AnimationControllerComponent");
    return true;
}

void AnimationControllerComponent::update(){
  if (current_animation == ""){
         Log::instance.warning("No animations to play!");
    }else{
        auto animation = m_animations_map[current_animation];
        if(next_animation != "" && animation->has_finished()){
	   change_animations();
	}
    }
}

void AnimationControllerComponent::add_animation(std::string name,
                                                 Animation & animation){
    if (m_animations_map.find(name) != m_animations_map.end()){
        Log::instance.warning("Animation " + name + " already exists!");
        return;
    }

    m_animations_map[name] = &animation;

    if (m_animations_map.size() == 1)
        current_animation = name;
}

void AnimationControllerComponent::play_animation(std::string name, bool wait_to_finish){
    Log::instance.info("Play animation " + name );
    next_animation = name;
    m_animations_map[current_animation]->flipping(flip);

    if (!wait_to_finish)
        change_animations();
}

void AnimationControllerComponent::change_animations(){
    auto animation = m_animations_map[current_animation];
    animation->disable();

    current_animation = next_animation;
    next_animation = "";

    animation = m_animations_map[current_animation];
    animation->enable();
    animation->setup();
}

void AnimationControllerComponent::flipping(bool isFlip){
  flip = isFlip;
}

