#ifndef __MENU_SCENE__
#define __MENU_SCENE__

#include "scene.hpp"
#include "button.hpp"
#include "Sprite.h"

class MenuScene : public engine::Scene {
public:
    MenuScene() : engine::Scene("Menu") {}

    ~MenuScene() {}

    bool init(SDL_Renderer *main_canvas);
    bool off();

    bool draw(SDL_Renderer *main_canvas);
};

#endif
