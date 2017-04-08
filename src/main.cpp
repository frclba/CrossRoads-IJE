#include "game.hpp"
#include "menu_scene.hpp"

using namespace engine;

int main(int, char **){

    std::pair<int, int> window_size(800, 600);

    MenuScene menu_scene;
    
    Game::instance.set_properties("Game", window_size);

    Game::instance.add_scene(menu_scene);
    Game::instance.run();

    return 0;
}
