#include<scene.hpp>
#include "components/animation.hpp"

using namespace engine;
class MenuScene : public Scene{
    public:

        MenuScene(std::string name):
            Scene(name){}

        ~MenuScene();

    void game_logic();
    void buttons_controller();

    private:


};
