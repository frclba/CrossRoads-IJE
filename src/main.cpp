#include "game.hpp"
#include "menu_scene.hpp"

using namespace engine;

int main(int, char **){

    std::pair<int, int> window_size(800, 600);

    MenuScene menu_scene;
    Game game("Teste", window_size);
    game.add_scene(menu_scene);
    game.run();

    return 0;
}
