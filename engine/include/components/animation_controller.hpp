#ifndef __ENGINE_COMPONENTS_ANIMATION_CONTROLLER__
#define __ENGINE_COMPONENTS_ANIMATION_CONTROLLER__

#include <string>
#include <unordered_map>
#include <utility>
#include "sdl2core.hpp"

#include "components/component.hpp"
#include "components/animation.hpp"
#include "gameobject.hpp"

namespace engine {
    class AnimationControllerComponent : public Component {
        public:
            AnimationControllerComponent(GameObject &main_game_object, std::string id)
                : Component(main_game_object, id), current_animation(""), next_animation("") {}

            ~AnimationControllerComponent(){};

            bool init();
            bool shutdown();
            void update();

            void add_animation(std::string name, Animation &animation);

            void play_animation(std::string name, bool wait_to_finish=false);

            void flipping(bool isFlip);
        private:
            bool flip;
            std::unordered_map<std::string, Animation *> m_animations_map;
            std::string current_animation;
            std::string next_animation;

            void change_animations();
    };
}

#endif
