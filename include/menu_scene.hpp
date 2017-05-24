#include<scene.hpp>
#include "components/animation.hpp"
#include "components/Sound.hpp"

using namespace engine;
class MenuScene : public Scene{
    public:

        MenuScene(std::string name):
            Scene(name){}

        ~MenuScene();

    void game_logic();
    void buttons_controller();

    void init_sounds();

    private:
      Mix_Chunk* button_hover_in_Sound;

};
