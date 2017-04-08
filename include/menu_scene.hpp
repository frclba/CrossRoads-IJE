#ifndef __MENU_SCENE__
#define __MENU_SCENE__

// using namespace engine;

#include "scene.hpp"
#include "button.hpp"
#include "Sprite.h"
#include "Timer.hpp"
#include "Music.hpp"
#include "Sound.hpp"

class MenuScene : public engine::Scene {
    public:
        MenuScene() : engine::Scene("Menu") {}

        ~MenuScene() {}

        bool init(SDL_Renderer *main_canvas);
        bool off();

        bool draw(SDL_Renderer *main_canvas,Timer *timer);

    private:
        int mouseX;
        int mouseY;
        Button *player;
        Sprite *fire;
        Music *music;
        Sound *button_grab;
};
#endif
