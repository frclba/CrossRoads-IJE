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
#include "player.hpp"
#include "restart.hpp"

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

    //TODO - Put in a specific place where it belongs with large scalability
    Music menu_music(background, "menu_musicBackground", "assets/music/gm.wav");

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
    Sound button_hover_sound(bLoad, "button_hover_sound", "assets/sounds/button_grab.wav");

    //coloca o tempo que a nimacao do fogo percorre.
    animationFire.setDelay(100);

    //Adiciona components aos gameobjects
    background.add_component(backgroundImage);
    background.add_component(menu_music);
    menuFire.add_component(animationFire);
    bNew.add_component(image_bNew);
    bLoad.add_component(image_bLoad);
    bLoad.add_component(button_hover_sound);

    //adiciona game objects ao menu
    menu.add_game_object(menuFire);
    menu.add_game_object(bNew);
    menu.add_game_object(bLoad);
    menu.add_game_object(background);

    // =================================== STAGE 1 =======================================
    Log::instance.jumpLine("Starting configurations && Instantiations\n");

    //Criando cena da fase
    Stage1Scene stage1("Fase 1");
    Game::instance.add_scene(stage1);

    GameObject player("player",true,"player");
    GameObject plataform("plataform",true,"ground");
    GameObject monster("monster",true,"monster");
    GameObject background_stage1("backgroundForest");
    GameObject ground_stage1("ground",true,"ground");

    Music stage1_music(background_stage1, "menu_musicStage1", "assets/music/battle.mp3");
    ImageComponent backgroundForest(background_stage1,"backgroundForest", "assets/sprites/backgroundFloresta.png");

    //ImageComponent tile1(ground_stage1, "tile1", "/usr/share/crossroads/assets/sprites/ChãoMap1.png");

    background_stage1.set_layer(GameObject::Layer::background);

    ImageComponent tile1(ground_stage1, "tile1", "assets/sprites/ChãoMap1.png");
    ImageComponent tile2(ground_stage1,"tile2", "assets/sprites/ChãoMap2.png");
    ImageComponent tile3(ground_stage1,"tile3", "assets/sprites/ChãoMap3.png");
    ImageComponent tile4(ground_stage1,"tile4", "assets/sprites/ChãoMap4.png");

    ImageComponent img_plataform(plataform,"plataform", "assets/sprites/plataform.png");
    plataform.add_component(img_plataform);

    AnimationControllerComponent player_anim_ctrl(player, "animationController");
    AnimationControllerComponent monster_anim_ctrl(player, "monster_controler");

    // Player Animations
    Animation player_idle(player, "playerIdle", "assets/sprites/hero.png",480/8,49, 8);
    Animation player_running(player, "playerRunning", "assets/sprites/hero_running.png" ,220/4, 46, 4);
    Animation player_attack(player, "playerAttack", "assets/sprites/attack.png" ,825/11, 49, 11);
    Animation player_damage(player, "playerDamage", "assets/sprites/damage.png" ,800/8, 50, 8);
    // Monster Animations
    Animation monster_walk(monster, "monster_walk", "assets/sprites/monster_walk.png" ,153/4, 38, 4);
    Animation monster_damage(monster, "monster_damage", "assets/sprites/monster_damage.png" ,153/4, 38, 4);

    player_idle.setDelay(100);
    player_running.setDelay(100);
    player_attack.setDelay(30);
    player_damage.setDelay(100);
    monster_walk.setDelay(50);
    monster_damage.setDelay(100);

    GameObject attack_box("attack_box",true,"attack_box",GameObject::State::disabled);

    //Monster artificial intelligence controller
    MonsterAI monster_ai(monster, "monster_ai",&player,&monster_anim_ctrl);
    monster_anim_ctrl.add_animation("monster_walk",monster_walk);
    monster_anim_ctrl.add_animation("monster_damage",monster_damage);
    monster.add_component(monster_walk);
    monster.add_component(monster_damage);
    monster.add_component(monster_anim_ctrl);
    monster.add_component(monster_ai);

    Player player_logic(player,"player_logic",&player_anim_ctrl,attack_box);

    //Adding animation to animation mananger
    player_anim_ctrl.add_animation("player_idle", player_idle);
    player_anim_ctrl.add_animation("player_running", player_running);
    player_anim_ctrl.add_animation("player_attack", player_attack);
    player_anim_ctrl.add_animation("player_damage", player_damage);

    //Adding componentes to player
    player.add_component(player_idle);
    player.add_component(player_running);
    player.add_component(player_attack);
    player.add_component(player_damage);
    player.add_component(player_anim_ctrl);
    player.add_component(player_logic);

    player.main_positionY = 502;

    background_stage1.add_component(backgroundForest);
    background_stage1.add_component(stage1_music);

    // Adding defined gameobjects to stage 1 scene
    stage1.add_game_object(player);
    stage1.add_game_object(attack_box);
    stage1.add_game_object(monster);
    stage1.add_game_object(plataform);
    stage1.add_game_object(ground_stage1);
    stage1.add_game_object(background_stage1);

    //==================================== WIN SCREEN =============================================
    Scene win("Win Scene");
    Game::instance.add_scene(win);

    GameObject win_background("win_background");
    ImageComponent image_win (win_background, "image_win", "assets/sprites/new_win.png");
    Restart restart_button_win(win_background, "restart_button_win");

    win_background.add_component(image_win);
    win_background.add_component(restart_button_win);

    win.add_game_object(win_background);

    //==================================== WIN SCREEN =============================================
    Scene lose("Lose Scene");
    Game::instance.add_scene(lose);

    GameObject lose_background("lose_background");
    ImageComponent image_lose (lose_background, "image_lose", "assets/sprites/lose.jpg");
    Restart restart_button_lose(lose_background, "restart_button_lose");

    lose_background.add_component(image_lose);
    lose_background.add_component(restart_button_lose);

    lose.add_game_object(lose_background);

    //==================================== GAME LOOP ============================================
    Log::instance.jumpLine("Ending Instantiations. Running Game\n");
    Game::instance.run();

    return 0;
}
