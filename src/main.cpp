#include "game.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include "components/image.hpp"
#include "sdl2core.hpp"

using namespace engine;

int main(int, char **){

    //Configurando nome e tamanho
    std::pair<int, int> window_size(800, 600);
    Game::instance.set_properties("Nome do Jogo",window_size);

    //Criando cena do menu
    Scene menu("Main Menu");
    Game::instance.add_scene(menu);

    GameObject background("background");
    ImageComponent backgroundImage(background, "assets/sprites/menu.png");

    background.add_component(backgroundImage);
    menu.add_game_object(background);


    //Game lopp
    Game::instance.run();

    return 0;
}
