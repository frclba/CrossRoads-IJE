#include <scene.hpp>
#include "components/animation.hpp"
#include "components/audio.hpp"

using namespace engine;

class MenuScene : public Scene {

public:

    MenuScene(std::string name) : Scene(name), enter(false) {}
    ~MenuScene();

    void game_logic();
    void buttons_controller();

    void init_sounds();

private:

    bool enter;
    AudioComponent *button_hover_in_Sound;

    // Mix_Chunk* button_hover_in_Sound;

};
