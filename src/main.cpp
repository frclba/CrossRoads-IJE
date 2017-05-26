#include "game.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include "components/image.hpp"
#include "components/animation.hpp"
#include "components/animation_controller.hpp"
#include "components/music.hpp"
#include "sdl2core.hpp"
#include "menu_scene.hpp"
#include "stage1_scene.hpp"

#include "monsterAI.hpp"

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
    GameObject plataform("plataform");
    GameObject monster("monster");
    GameObject background_stage1("backgroundForest");
    GameObject ground_stage1("ground");

    ImageComponent backgroundForest(background_stage1,"backgroundForest", "assets/sprites/backgroundFloresta.png");

    ImageComponent tile1(ground_stage1, "tile1", "assets/sprites/ChãoMap1.png");
    ImageComponent tile2(ground_stage1,"tile2", "assets/sprites/ChãoMap2.png");
    ImageComponent tile3(ground_stage1,"tile3", "assets/sprites/ChãoMap3.png");
    ImageComponent tile4(ground_stage1,"tile4", "assets/sprites/ChãoMap4.png");

    ImageComponent img_plataform(plataform,"plataform", "assets/sprites/plataform.png");
    plataform.add_component(img_plataform);
    
    AnimationControllerComponent animCtrl(player, "animationController");
    AnimationControllerComponent monster_controler(player, "monster_controler");

    Animation player_idle(player, "playerIdle", "assets/sprites/hero.png",800/8,50, 8);
    player_idle.setDelay(100);

    Animation player_running(player, "playerRunning", "assets/sprites/hero_running.png" ,220/4, 46, 4);
    player_running.setDelay(100);

    Animation player_attack(player, "playerAttack", "assets/sprites/attack.png" ,836/11, 50, 11);
    player_attack.setDelay(50);

    Animation player_damage(player, "playerDamage", "assets/sprites/damage.png" ,800/8, 50, 8);
    player_damage.setDelay(100);

    
    Animation monster_walk(monster, "monster_walk", "assets/sprites/monster_walk.png" ,153/4, 38, 4);
    monster_walk.setDelay(50);

    MonsterAI monster_ai(monster, "monster_ai",&player,&monster_controler);
    monster_controler.add_animation("monster_walk",monster_walk);
    monster.add_component(monster_walk);
    monster.add_component(monster_controler);
    monster.add_component(monster_ai);

    animCtrl.add_animation("player_idle", player_idle);
    animCtrl.add_animation("player_running", player_running);
    animCtrl.add_animation("player_attack", player_attack);
    animCtrl.add_animation("player_damage", player_damage);
    player.add_component(player_idle);
    player.add_component(player_running);
    player.add_component(player_attack);
    player.add_component(player_damage);
    player.add_component(animCtrl);
    player.main_positionY = 502;



    background_stage1.add_component(backgroundForest);

    ground_stage1.add_component(tile1);
    ground_stage1.main_positionX = 0;
    ground_stage1.main_positionY = 552;
    ground_stage1.add_component(tile2);
    ground_stage1.add_component(tile3);
    ground_stage1.add_component(tile4);


    
    stage1.add_game_object(player);
    stage1.add_game_object(monster);
    stage1.add_game_object(plataform);
    stage1.add_game_object(ground_stage1);
    stage1.add_game_object(background_stage1);
    //==================================== GAME LOOP ============================================

    Game::instance.run();

    return 0;
}
