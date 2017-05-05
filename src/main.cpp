#include "game.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include "components/image.hpp"
#include "components/animation.hpp"
#include "components/music.hpp"
#include "sdl2core.hpp"
#include "menu_scene.hpp"
#include "stage1_scene.hpp"

using namespace engine;

int main(int, char **){

    //Configurando nome e tamanho
    std::pair<int, int> window_size(800, 600);
    Game::instance.set_properties("Nome do Jogo",window_size);

    //================================================= MENU =======================================
    MenuScene menu("Main Menu");
    Game::instance.add_scene(menu);

    GameObject background("background");
    ImageComponent backgroundImage(background,"imageBackground", "assets/sprites/menu.png");
    MusicComponent musica(background, "musicaBackground", "assets/music/gm.wav");

    GameObject menuFire("menuFire");
    Animation animationFire(menuFire,"imageFire", "assets/sprites/menuFire.png",348/6,76,6);

    GameObject bNew("bNew");
    Animation image_bNew(bNew,"imageBNew", "assets/sprites/bNew.png",448/2,100,2);

    //cadastrando dois tipos de animação, ado butao normal que pega a imagem de 0 a 0 e a mouseON que pega a imagem de 1 a 1
    image_bNew.setAnimation("normal",0,0);
    image_bNew.setAnimation("mouseON",1,1);

    GameObject bLoad("bLoad");
    Animation image_bLoad(bLoad,"imageBLoad","assets/sprites/bLoad.png",448/2,100,2);
    image_bLoad.setAnimation("normal",0,0);
    image_bLoad.setAnimation("mouseON",1,1);

    //coloca o tempo que a nimacao do fogo percorre.
    animationFire.setDelay(100);

    //Adiciona components aos gameobjects
    background.add_component(backgroundImage);
    background.add_component(musica);
    menuFire.add_component(animationFire);
    bNew.add_component(image_bNew);
    bLoad.add_component(image_bLoad);

    //adiciona game objects ao menu
    menu.add_game_object(menuFire);
    menu.add_game_object(bNew);
    menu.add_game_object(bLoad);
    menu.add_game_object(background);

    // =================================== STAGE 1 =======================================

    //Criando cena da fase
    Stage1Scene stage1("Fase 1");
    Game::instance.add_scene(stage1);


    GameObject player("player");

    Animation player_idle(player, "playerIdle", "assets/sprites/tes.png",524/13,53, 13);
    player_idle.setDelay(100);
    player_idle.setAnimation("stay",0,2);
    player_idle.setAnimation("walk",3,11);
    player_idle.setAnimation("attack",12,12);
    player.add_component(player_idle);
    stage1.add_game_object(player);

    //==================================== GAME LOOP ============================================

    Game::instance.run();

    return 0;
}
