#include "game.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include "components/image.hpp"
#include "components/animation.hpp"
#include "components/animation_controller.hpp"
#include "components/audio.hpp"
#include "sdl2core.hpp"
#include "menu_scene.hpp"
#include "stage1_scene.hpp"
#include "monsterAI.hpp"
#include "player.hpp"
#include "restart.hpp"
#include "fireball.hpp"
#include "portal.hpp"
#include "cameraposition.hpp"
#include "heart.hpp"
#include "bossAI.hpp"
#include "initialStory.hpp"


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
    background.set_layer(GameObject::Layer::background);

    AudioComponent menu_music(background, "menu_musicBackground", "assets/music/menu.wav", true);

    GameObject menuFire("menuFire");
    Animation animationFire(menuFire,"imageFire", "assets/sprites/menuFire.png",348/6,76,6);

    GameObject bNew("bNew");
    Animation image_bNew(bNew,"imageBNew", "assets/sprites/bNew.png",448/2,100,2);

    GameObject title("title");
    ImageComponent image_title(title,"image_title", "assets/sprites/menu_title.png");
    title.add_component(image_title);

    //cadastrando dois tipos de animação, ado butao normal que pega a imagem de 0 a 0 e a mouseON que pega a imagem de 1 a 1
    image_bNew.setAnimation("normal",0,0);
    image_bNew.setAnimation("mouseON",1,1);

    GameObject bLoad("bLoad");
    Animation image_bLoad(bLoad,"imageBLoad","assets/sprites/bLoad.png",448/2,100,2);
    image_bLoad.setAnimation("normal",0,0);
    image_bLoad.setAnimation("mouseON",1,1);
    AudioComponent button_hover_sound(bLoad, "button_hover_sound", "assets/sounds/Game.menu.sound.(10).wav", false, false);

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
    menu.add_game_object(title);
    menu.add_game_object(background);

    // =================================== STAGE 1 =======================================
    Log::instance.jumpLine("Starting configurations && Instantiations\n");

    //Criando cena da fase
    Stage1Scene stage1("Fase 1");
    Game::instance.add_scene(stage1);

    GameObject player("player",true,"player");

    GameObject bullet("bullet",true,"bullet");
    Animation img_bullet(bullet,"img_bullet","assets/sprites/cross.png",24,13,1);
    bullet.add_component(img_bullet);
    bullet.setState(GameObject::State::disabled);

    player.main_positionY = 502;
    player.set_layer(GameObject::Layer::layer3);
    GameObject background_stage1("backgroundForest");
    GameObject ground_stage1("ground",true,"ground");

    AudioComponent stage1_music(background_stage1, "menu_musicStage1", "assets/music/stage.wav", true);
    AudioComponent boss_music(background_stage1, "boss_music", "assets/music/boss.wav",true, false);

    AudioComponent player_running_audio(player, "player_running_audio", "assets/sounds/Passo.4.wav", false, false);
    AudioComponent player_running_audio2(player, "player_running_audio2", "assets/sounds/Passo.2.wav", false, false);
    AudioComponent player_attack_audio(player, "player_attack_audio", "assets/sounds/ataque.wav", false, false);
    AudioComponent player_jump_audio(player, "player_jump_audio", "assets/sounds/pulo.herói.2.wav", false, false);
    AudioComponent player_low_life_audio(player, "player_low_life_audio", "assets/sounds/Coracao.batendo.wav", false, false);
    AudioComponent player_arrow_sound(player, "player_arrow_sound", "assets/sounds/Game.menu.sound.(1).wav", false, false);


    background_stage1.add_component(stage1_music);
    background_stage1.add_component(boss_music);

    player.add_component(player_running_audio);
    player.add_component(player_running_audio2);
    player.add_component(player_attack_audio);
    player.add_component(player_jump_audio);
    player.add_component(player_low_life_audio);
    player.add_component(player_arrow_sound);

    ImageComponent backgroundForest(background_stage1,"backgroundForest", "assets/sprites/backgroundFloresta.png");
    backgroundForest.set_back_rect(800,600);
    background_stage1.set_layer(GameObject::Layer::background);

    ImageComponent tile1(ground_stage1, "tile1", "assets/sprites/ChãoMap1.png");
    ImageComponent tile2(ground_stage1,"tile2", "assets/sprites/ChãoMap2.png");
    ImageComponent tile3(ground_stage1,"tile3", "assets/sprites/ChãoMap3.png");
    ImageComponent tile4(ground_stage1,"tile4", "assets/sprites/ChãoMap4.png");


    AnimationControllerComponent player_anim_ctrl(player, "animationController");
    AnimationControllerComponent monster_anim_ctrl(player, "monster_controler");

    // Player Animations
    Animation player_idle(player, "playerIdle", "assets/sprites/hero.png",480/8,49, 8);
    Animation player_running(player, "playerRunning", "assets/sprites/hero_running.png" ,220/4, 46, 4);
    Animation player_attack(player, "playerAttack", "assets/sprites/attack.png" ,825/11, 49, 11);
    Animation player_ranged(player, "playerAttackRanged", "assets/sprites/cross_attack.png" ,252/7, 45, 7);
    Animation player_damage(player, "playerDamage", "assets/sprites/damage.png" ,800/8, 50, 8);

    player_idle.setDelay(100);
    player_running.setDelay(100);
    player_attack.setDelay(30);
    player_ranged.setDelay(50);
    player_damage.setDelay(100);
    GameObject attack_box("attack_box",true,"attack_box",GameObject::State::disabled);

    //monsters
    GameObject monster1("monster1",true,"monster");
    AnimationControllerComponent monster_anim_ctrl1(player, "monster_controler");

    Animation monster_walk1(monster1, "monster_walk1", "assets/sprites/monster_walk.png" ,153/4, 38, 4);
    Animation monster_damage1(monster1, "monster_damage1", "assets/sprites/monster_damage.png" ,153/4, 38, 4);
    Animation monster_attack1(monster1, "monster_attack1", "assets/sprites/monster_attack.png" ,184/4, 40, 4);
    monster_walk1.setDelay(50);
    monster_damage1.setDelay(100);
    monster_attack1.setDelay(100);

    //Monster artificial intelligence controller
    MonsterAI monster_ai1(monster1, "monster_ai1",&player,&monster_anim_ctrl);
    monster_anim_ctrl.add_animation("monster_walk",monster_walk1);
    monster_anim_ctrl.add_animation("monster_damage",monster_damage1);
    monster_anim_ctrl.add_animation("monster_attack",monster_attack1);
    monster1.add_component(monster_walk1);
    monster1.add_component(monster_damage1);
    monster1.add_component(monster_attack1);
    monster1.add_component(monster_anim_ctrl1);
    monster1.add_component(monster_ai1);

    GameObject monster2("monster2",true,"monster");
    AnimationControllerComponent monster_anim_ctrl2(player, "monster_controler");

    Animation monster_walk2(monster2, "monster_walk2", "assets/sprites/monster_walk.png" ,153/4, 38, 4);
    Animation monster_damage2(monster2, "monster_damage2", "assets/sprites/monster_damage.png" ,153/4, 38, 4);
    Animation monster_attack2(monster2, "monster_attack2", "assets/sprites/monster_attack.png" ,184/4, 40, 4);
    monster_walk2.setDelay(50);
    monster_damage2.setDelay(100);
    monster_attack2.setDelay(100);

    //Monster artificial intelligence controller
    MonsterAI monster_ai2(monster2, "monster_ai2",&player,&monster_anim_ctrl2);
    monster_anim_ctrl2.add_animation("monster_walk",monster_walk2);
    monster_anim_ctrl2.add_animation("monster_damage",monster_damage2);
    monster_anim_ctrl2.add_animation("monster_attack",monster_attack2);
    monster2.add_component(monster_walk2);
    monster2.add_component(monster_damage2);
    monster2.add_component(monster_anim_ctrl2);
    monster2.add_component(monster_attack2);
    monster2.add_component(monster_ai2);

    GameObject monster3("monster3",true,"monster");
    AnimationControllerComponent monster_anim_ctrl3(player, "monster_controler");

    Animation monster_walk3(monster3, "monster_walk3", "assets/sprites/monster_walk.png" ,153/4, 38, 4);
    Animation monster_damage3(monster3, "monster_damage3", "assets/sprites/monster_damage.png" ,153/4, 38, 4);
    Animation monster_attack3(monster3, "monster_attack3", "assets/sprites/monster_attack.png" ,184/4, 40, 4);
    monster_walk3.setDelay(50);
    monster_damage3.setDelay(100);
    monster_attack3.setDelay(100);

    //Monster artificial intelligence controller
    MonsterAI monster_ai3(monster3, "monster_ai",&player,&monster_anim_ctrl);
    monster_anim_ctrl3.add_animation("monster_walk",monster_walk3);
    monster_anim_ctrl3.add_animation("monster_damage",monster_damage3);
    monster_anim_ctrl3.add_animation("monster_attack",monster_attack3);
    monster3.add_component(monster_walk3);
    monster3.add_component(monster_damage3);
    monster3.add_component(monster_attack3);
    monster3.add_component(monster_anim_ctrl3);
    monster3.add_component(monster_ai3);

    GameObject monster4("monster4",true,"monster");
    AnimationControllerComponent monster_anim_ctrl4(player, "monster_controler");

    Animation monster_walk4(monster4, "monster_walk4", "assets/sprites/monster_walk.png" ,153/4, 38, 4);
    Animation monster_damage4(monster4, "monster_damage4", "assets/sprites/monster_damage.png" ,153/4, 38, 4);
    Animation monster_attack4(monster4, "monster_attack4", "assets/sprites/monster_attack.png" ,184/4, 40, 4);
    monster_walk4.setDelay(50);
    monster_damage4.setDelay(100);
    monster_attack4.setDelay(100);
    //Monster artificial intelligence controller
    MonsterAI monster_ai4(monster4, "monster_ai4",&player,&monster_anim_ctrl4);
    monster_anim_ctrl4.add_animation("monster_walk",monster_walk4);
    monster_anim_ctrl4.add_animation("monster_damage",monster_damage4);
    monster_anim_ctrl4.add_animation("monster_attack",monster_attack4);
    monster4.add_component(monster_walk4);
    monster4.add_component(monster_damage4);
    monster4.add_component(monster_anim_ctrl4);
    monster4.add_component(monster_attack4);
    monster4.add_component(monster_ai4);

    //.monsters
    AudioComponent goblin_spawn_audio(monster1, "goblin_spawn_audio", "assets/sounds/vocalizacoes.goblin.wav", false, false);
    AudioComponent goblin_aggro_audio(monster1, "goblin_aggro_audio", "assets/sounds/vocalizacoes.goblin.3.wav", false, false);

    monster1.add_component(goblin_spawn_audio);
    monster1.add_component(goblin_aggro_audio);

    // Animação da setinha
    GameObject go_arrow("go_arrow");
    go_arrow.main_positionX = 600;
    go_arrow.main_positionY = 100;
    Animation go_arrow_anim(go_arrow,"go_arrow_anim","assets/sprites/arrow.png",200,200,10);
    go_arrow_anim.setDelay(200);
    go_arrow.add_component(go_arrow_anim);

    //Portal
    GameObject portal("portal");
    portal.set_layer(GameObject::Layer::layer1);
    Animation portal_img(portal,"portal","assets/sprites/portal.png",240/4,80,4);
    portal_img.setDelay(50);
    CameraPosition portal_pos(portal,"portal_pos",&backgroundForest,600,470);

    Portal portal_logic(portal,"portal_logic",&backgroundForest,&portal_pos);
    portal.add_component(portal_img);
    portal.add_component(portal_logic);
    portal.add_component(portal_pos);

    portal_logic.add_monster(&monster1);
    portal_logic.add_monster(&monster2);
    portal_logic.add_monster(&monster3);
    portal_logic.add_monster(&monster4);


    Player player_logic(player,"player_logic",&player_anim_ctrl,attack_box,&backgroundForest);

    //Adding animation to animation mananger
    player_anim_ctrl.add_animation("player_idle", player_idle);
    player_anim_ctrl.add_animation("player_running", player_running);
    player_anim_ctrl.add_animation("player_attack", player_attack);
    player_anim_ctrl.add_animation("player_ranged", player_ranged);
    player_anim_ctrl.add_animation("player_damage", player_damage);

    //Adding componentes to player
    player.add_component(player_idle);
    player.add_component(player_running);
    player.add_component(player_attack);
    player.add_component(player_ranged);
    player.add_component(player_damage);
    player.add_component(player_anim_ctrl);
    player.add_component(player_logic);

    background_stage1.add_component(backgroundForest);


    //plataforms
    //part1
    GameObject plataform("plataform",true,"ground");
    ImageComponent img_plataform(plataform,"plataform", "assets/sprites/plataform.png");
    CameraPosition plataform_ai(plataform,"plataform_ai",&backgroundForest, 550, 350);
    plataform.add_component(plataform_ai);
    plataform.add_component(img_plataform);

    GameObject plataform2("plataform2",true,"ground");
    ImageComponent img_plataform2(plataform2,"plataform2", "assets/sprites/plataform.png");
    CameraPosition plataform_ai2(plataform2,"plataform_ai2",&backgroundForest, 200, 200);
    plataform2.add_component(plataform_ai2);
    plataform2.add_component(img_plataform2);

    GameObject plataform3("plataform3",true,"ground");
    ImageComponent img_plataform3(plataform3,"plataform3", "assets/sprites/plataform.png");
    CameraPosition plataform_ai3(plataform3,"plataform_ai3",&backgroundForest,100,400);
    plataform3.add_component(plataform_ai3);
    plataform3.add_component(img_plataform3);
    //part2
    GameObject plataform4("plataform",true,"ground");
    ImageComponent img_plataform4(plataform4,"plataform4", "assets/sprites/plataform.png");
    CameraPosition plataform_ai4(plataform4,"plataform_ai4",&backgroundForest,600,350);
    plataform4.add_component(plataform_ai4);
    plataform4.add_component(img_plataform4);

    GameObject plataform5("plataform5",true,"ground");
    ImageComponent img_plataform5(plataform5,"plataform5", "assets/sprites/plataform.png");
    CameraPosition plataform_ai5(plataform5,"plataform_ai5",&backgroundForest,900,200);
    plataform5.add_component(plataform_ai5);
    plataform5.add_component(img_plataform5);

    GameObject plataform6("plataform6",true,"ground");
    ImageComponent img_plataform6(plataform6,"plataform6", "assets/sprites/plataform.png");
    CameraPosition plataform_ai6(plataform6,"plataform_ai6",&backgroundForest,1200,400);
    plataform6.add_component(plataform_ai6);
    plataform6.add_component(img_plataform6);
    //part3
    GameObject plataform7("plataform7",true,"ground");
    ImageComponent img_plataform7(plataform7,"plataform7", "assets/sprites/plataform.png");
    CameraPosition plataform_ai7(plataform7,"plataform_ai7",&backgroundForest,1500,350);
    plataform7.add_component(plataform_ai7);
    plataform7.add_component(img_plataform7);

    GameObject plataform8("plataform8",true,"ground");
    ImageComponent img_plataform8(plataform8,"plataform8", "assets/sprites/plataform.png");
    CameraPosition plataform_ai8(plataform8,"plataform_ai8",&backgroundForest,1800,200);
    plataform8.add_component(plataform_ai8);
    plataform8.add_component(img_plataform8);

    GameObject plataform9("plataform9",true,"ground");
    ImageComponent img_plataform9(plataform9,"plataform9", "assets/sprites/plataform.png");
    CameraPosition plataform_ai9(plataform9,"plataform_ai9",&backgroundForest,2000,400);
    plataform9.add_component(plataform_ai9);
    plataform9.add_component(img_plataform9 );


    //boss plataforms

    GameObject plataform10("plataform10", true, "ground");
    ImageComponent img_plataform10(plataform10, "plataform10", "assets/sprites/plataform.png");
    CameraPosition plataform_ai10(plataform10, "plataform_ai10", &backgroundForest, 2650, 370);
    plataform10.add_component(plataform_ai10);
    plataform10.add_component(img_plataform10);

    GameObject plataform11("plataform11", true, "ground");
    ImageComponent img_plataform11(plataform11, "plataform11", "assets/sprites/plataform.png");
    CameraPosition plataform_ai11(plataform11, "plataform_ai11", &backgroundForest, 2300, 400);
    plataform11.add_component(plataform_ai11);
    plataform11.add_component(img_plataform11);

    GameObject plataform12("plataform12",true,"ground");
    ImageComponent img_plataform12(plataform12,"plataform12", "assets/sprites/plataform.png");
    CameraPosition plataform_ai12(plataform12,"plataform_ai12", &backgroundForest, 2400, 200);
    plataform12.add_component(plataform_ai12);
    plataform12.add_component(img_plataform12);



    //.plataforms

    GameObject fireball("fireball",true,"fireball");
    fireball.main_positionX = 200;

    FireballController fireball_controller(fireball, "fireball", 15, &player);
    fireball.add_component(fireball_controller);

    Animation img_fireball(fireball,"fireball", "assets/sprites/meteoro.png",144/3,72,3);
    img_fireball.setDelay(100);
    fireball.add_component(img_fireball);
    fireball.setState(GameObject::State::disabled);
    AudioComponent fireball_droping_audio(fireball, "fireball_droping_audio", "assets/sounds/meteoro1.1.wav", false, false);
    fireball.add_component(fireball_droping_audio);

    GameObject boss("boss",true,"boss");
    boss.main_positionX = 600;
    boss.main_positionY = 300;
    CameraPosition boss_pos(boss,"boss_pos",&backgroundForest,2800,320);

    Animation boss_idle(boss, "bossIdle", "assets/sprites/boss.png",552/3,244, 3);
    Animation boss_dash(boss, "bossIdle", "assets/sprites/dash.png",2560/10,240, 10);
    Animation boss_howl(boss, "bossIdle", "assets/sprites/rugido.png",1288/7,256, 7);

    boss_idle.setDelay(220);
    boss_dash.setDelay(50);
    boss_howl.setDelay(200);

    AnimationControllerComponent boss_anim_ctrl(boss, "boss_controler");
    boss_anim_ctrl.add_animation("boss_idle",boss_idle);
    boss_anim_ctrl.add_animation("boss_dash",boss_dash);
    boss_anim_ctrl.add_animation("boss_howl",boss_howl);

    Boss boss_ai(boss,"boss_ai",&boss_anim_ctrl,&fireball,&boss_pos,&player);

    AudioComponent boss_dash_audio(boss, "boss_dash_audio", "assets/sounds/dash.wav", false, false);
    AudioComponent boss_full_putasso_audio(boss, "boss_full_putasso_audio", "assets/sounds/Ferimento.wav", false, false);

    boss.add_component(boss_idle);
    boss.add_component(boss_dash);
    boss.add_component(boss_howl);
    boss.add_component(boss_anim_ctrl);
    boss.add_component(boss_ai);
    boss.add_component(boss_pos);

    boss.add_component(boss_dash_audio);
    boss.add_component(boss_full_putasso_audio);

    //player life
    GameObject heart1("heart1");
    ImageComponent heart1_img(heart1,"heart1_img", "assets/sprites/heart.png");
    Heart heart1_controller(heart1,"heart1_controller",&player_logic,1);
    heart1.add_component(heart1_img);
    heart1.add_component(heart1_controller);

    GameObject heart2("heart2");
    ImageComponent heart2_img(heart2,"heart2_img", "assets/sprites/heart.png");
    Heart heart2_controller(heart2,"heart1_controller",&player_logic,2);
    heart2.add_component(heart2_img);
    heart2.add_component(heart2_controller);

    GameObject heart3("heart3");
    ImageComponent heart3_img(heart3,"heart3_img", "assets/sprites/heart.png");
    Heart heart3_controller(heart3,"heart3_controller",&player_logic,3);
    heart3.add_component(heart3_img);
    heart3.add_component(heart3_controller);

    GameObject heart4("heart4");
    ImageComponent heart4_img(heart4,"heart4_img", "assets/sprites/heart.png");
    Heart heart4_controller(heart4,"heart4_controller",&player_logic,4);
    heart4.add_component(heart4_img);
    heart4.add_component(heart4_controller);

    GameObject heart5("heart5");
    ImageComponent heart5_img(heart5,"heart5_img", "assets/sprites/heart.png");
    Heart heart5_controller(heart5,"heart5_controller",&player_logic,5);
    heart5.add_component(heart5_img);
    heart5.add_component(heart5_controller);

    heart1.main_positionX = 1 * 40;
    heart2.main_positionX = 2 * 40;
    heart3.main_positionX = 3 * 40;
    heart4.main_positionX = 4 * 40;
    heart5.main_positionX = 5 * 40;

    heart1.main_positionY = 55;
    heart2.main_positionY = 55;
    heart3.main_positionY = 55;
    heart4.main_positionY = 55;
    heart5.main_positionY = 55;


    //player life.


    // Adding defined gameobjects to stage 1 scene
    //portal.setState(GameObject::State::disabled);
    stage1.add_game_object(player);
    stage1.add_game_object(heart1);
    stage1.add_game_object(heart2);
    stage1.add_game_object(heart3);
    stage1.add_game_object(heart4);
    stage1.add_game_object(heart5);
    stage1.add_game_object(bullet);
    stage1.add_game_object(go_arrow);
    stage1.add_game_object(attack_box);
    stage1.add_game_object(monster1);
    stage1.add_game_object(monster2);
    stage1.add_game_object(monster3);
    stage1.add_game_object(monster4);
    stage1.add_game_object(portal);
    stage1.add_game_object(plataform);
    stage1.add_game_object(plataform2);
    stage1.add_game_object(plataform3);
    stage1.add_game_object(plataform4);
    stage1.add_game_object(plataform5);
    stage1.add_game_object(plataform6);
    stage1.add_game_object(plataform7);
    stage1.add_game_object(plataform8);
    stage1.add_game_object(plataform9);
    stage1.add_game_object(plataform10);
    stage1.add_game_object(plataform11);
    stage1.add_game_object(plataform12);
    stage1.add_game_object(ground_stage1);
    stage1.add_game_object(background_stage1);
    stage1.add_game_object(fireball);
    stage1.add_game_object(boss);

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
    //ImageComponent image_lose (lose_background, "image_lose", "assets/sprites/lose.jpg");
    Animation image_lose(lose_background,"image_lose","assets/sprites/LoseScreen.png",4800/6,600,6);
    image_lose.setDelay(100);

    Restart restart_button_lose(lose_background, "restart_button_lose");

    lose_background.add_component(image_lose);
    lose_background.add_component(restart_button_lose);

    lose.add_game_object(lose_background);


    //=====================================Initial Story======================================//
    Scene initial_story("initial_story");
    Game::instance.add_scene(initial_story);

    GameObject story("story");
    Animation story_anim1 (story, "story_anim1", "assets/sprites/st1.png",800,600,1);
    Animation story_anim2 (story, "story_anim2", "assets/sprites/init_story1.png",5600/7,600,7);
    Animation story_anim3 (story, "story_anim3", "assets/sprites/st2.png",800,600,1);
    Animation story_anim4 (story, "story_anim4", "assets/sprites/init_story2.png",5600/7,600,7);
    AnimationControllerComponent story_anim_controller(story,"stary_controller");

    story_anim_controller.add_animation("story1", story_anim1);
    story_anim_controller.add_animation("story2", story_anim2);
    story_anim_controller.add_animation("story3", story_anim3);
    story_anim_controller.add_animation("story4", story_anim4);
    story_anim2.setDelay(500);
    story_anim4.setDelay(500);

    InitialStory story_controller(story,"story_controller",&story_anim_controller);

    story.add_component(story_anim1);
    story.add_component(story_anim2);
    story.add_component(story_anim3);
    story.add_component(story_anim4);
    story.add_component(story_anim_controller);
    story.add_component(story_controller);

    initial_story.add_game_object(story);

    //==================================== GAME LOOP ============================================
    Log::instance.jumpLine("Ending Instantiations. Running Game\n");
    Game::instance.run();

    return 0;
}
