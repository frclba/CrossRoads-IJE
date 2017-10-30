/**
    \file menu_scene.hpp
    This file declares the MenuScene class
*/
#include <scene.hpp>
#include "components/animation.hpp"
#include "components/audio.hpp"

using namespace engine;

/**
    \class MenuScene
    This class is responsible for managing the game scene.
*/
class MenuScene : public Scene {

public:

    /**
        Declares the contructor, defining the initial values
        of the members.
    */
    MenuScene(std::string name) : Scene(name) {}
    ~MenuScene();


private:

    // Declares the prototype of the menu scene functions
    void game_logic();
    void new_game_button_controller();
    void load_button_controller();
    void detect_scene_pass();
    void init_sounds();

    AudioComponent *button_hover_in_Sound;

};
