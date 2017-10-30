/**
    \file menu_scene.hpp
    This file declares the MenuScene class
*/
#include <scene.hpp>
#include "components/animation.hpp"
#include "components/audio.hpp"

using namespace engine;

/// Class to control of menu scene
/**
    \class MenuScene
    This class is responsible for managing the game scene.
*/
class MenuScene : public Scene {

public:

    MenuScene(std::string name) : Scene(name) {}
    ~MenuScene();


private:

    void game_logic();
    void new_game_button_controller();
    void load_button_controller();
    void detect_scene_pass();
    void init_sounds();

    AudioComponent *button_hover_in_Sound;

};
