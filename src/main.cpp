#include "game.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include "components/image.hpp"
#include "components/animation.hpp"
#include "sdl2core.hpp"
#include "menu_scene.hpp"

using namespace engine;

int main(int, char **){

    //Configurando nome e tamanho
    std::pair<int, int> window_size(800, 600);
    Game::instance.set_properties("Nome do Jogo",window_size);

    //Criando cena do menu
    MenuScene menu("Main Menu");
    Game::instance.add_scene(menu);

    GameObject background("background");
    ImageComponent backgroundImage(background, "assets/sprites/menu.png");

    GameObject im("im");
    Animation fImage(im, "assets/sprites/personagem.png",900/5,495/2,10);

    GameObject asd("asd");
    Animation fasd(asd, "assets/sprites/personagem.png",900/5,495/2,10);



    fImage.setDelay(100);

    background.add_component(backgroundImage);
    im.add_component(fImage);
    asd.add_component(fasd);

    asd.main_positionX = 50;
    asd.main_positionY = 50;

    menu.add_game_object(im);
    menu.add_game_object(asd);
    menu.add_game_object(background);
    //Game lopp
    Game::instance.run();

    return 0;
}
