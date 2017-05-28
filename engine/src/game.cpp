#include "game.hpp"

#define FRAME 60.0
using namespace engine;

Game Game::instance;

void Game::set_properties(std::string name, std::pair<int, int> window_size){
    main_name = name;
    main_window_size = window_size;
}

bool Game::startSDL(){

    Log::instance.info("Iniciando video e audio");

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        Log::instance.error("Error ao inicializar video ou audio");
        return false;
    }

    Log::instance.info("Iniciando Imagem");

    int img_flags = IMG_INIT_PNG; //Caso forem ser usados outros tipos de imagem, inserir as flags aqui
    if(!(IMG_Init(img_flags) & img_flags)){
        Log::instance.error("Erro ao inicializar imagens !");
        return false;
    }
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
        Log::instance.error("Erro ao inicializar mixer");
        return false;
    }

    timer = new Timer();
    mouse = new Mouse();
    keyboard = new Keyboard();
    collision_manager = new CollisionManager();
    return true;

}

bool Game::createWindow(){
    Log::instance.info("Criando janela");

    main_window = SDL_CreateWindow( main_name.c_str(),          //Titulo
                                    SDL_WINDOWPOS_CENTERED,     //Posicao em X
                                    SDL_WINDOWPOS_CENTERED,     //Posicao em Y
                                    main_window_size.first,     //Width
                                    main_window_size.second,    //Height
                                    SDL_WINDOW_SHOWN );         //Window flags
    if( main_window == NULL ){
        Log::instance.error("Falha ao criar janela");
        return false;
    }

    main_canvas = SDL_CreateRenderer( main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    if ( main_canvas == NULL ){
        Log::instance.error("Falha ao criar renderizador");
        return false;
    }

    SDL_SetRenderDrawColor( main_canvas,
        main_background_color.r,
        main_background_color.g,
        main_background_color.b,
        main_background_color.a );
        return true;
    }

    void Game::destroyWindow(){
        SDL_DestroyRenderer( main_canvas );
        main_canvas = NULL;

        SDL_DestroyWindow( main_window );
        main_window = NULL;
    }

    void Game::offSDL(){
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void Game::run(){
        current_state = State::init;

        if( startSDL() && createWindow() ){
            Log::instance.info("Iniciando o jogo");
            current_state = State::main_loop;

            unsigned int frame_time = 1000.0/ FRAME;

            timer->start();
           // current_scene->init();
           if(current_scene != NULL)
                current_state = State::main_loop_change_scene;

            while(current_state != State::exit_loop){

                if(handle_scene_changes() == false)
                    break;

                SDL_Event evt;

                //get mouse position
                mouse->set_position();
                while( SDL_PollEvent(&evt) != 0 ){
                    if( evt.type == SDL_QUIT ){
                        current_state = State::exit_loop;
                    }

                    keyboard->setKeys(&evt);
                    if( evt.type == SDL_KEYDOWN ){
                        switch (evt.key.keysym.sym) {
                            case SDLK_SPACE:
                                //Log::instance.debug("teste teclado");
                                //Keyboard::isKeyDown(keycode::KEY_SPACE);
                                break;

                        }
                    }
                }
		//	current_scene->get_collide_objects();
		collision_manager->getCollisions(current_scene->get_collide_objects());
		current_scene->update();
                current_scene->game_logic();
                //Limpa o Canvas visualizado pelo  usuário
                SDL_RenderClear(main_canvas);
                //Desenha no buffer secundário.
                current_scene->draw();
                //Exibe o Canvas secundário para o usuário
                SDL_RenderPresent(main_canvas);

                if( frame_time > timer->get_elapseTime()){
                    SDL_Delay( timer->get_elapseTime());
                }

                keyboard->clearKeyboard();
		current_scene->clear_collide_objects();
                timer->set_TimeStep();
            }

            Log::instance.info("Cleaning scene...");
            if(current_scene)
                current_scene->shutdown();
        }

        Log::instance.info("Desligando tudo");
        current_state = State::shutdown;
        destroyWindow();
        offSDL();
    }

bool Game::add_scene(Scene &scene){
    //Isso faz o id ser o name.
    auto id = scene.name();
    Log::instance.info("Adicionando cena. Nome da cena: " + id);

    //A scene desejada sempre tem que ser a ultima. Se não for, vai ser adicionada novamente.
    if( scenes_list.find(id) != scenes_list.end() ){
        Log::instance.warning("Essa cena já está carregada !");
        return false;
    }

    scenes_list[id] = &scene;

    if( current_scene == NULL )
        change_scene(id);

    return true;
}

bool Game::change_scene(const std::string &id){

    if( scenes_list.find(id) == scenes_list.end() ){
        return false;
    }

    last_current_scene = current_scene;

    // current_scene = scenes_list[id];
    if(next_scene == NULL){
        //Quando for rodado a primeira vez.
        current_scene = scenes_list[id];
    }else{
        printf("Pŕoxima cena que foi setada\n");
        next_scene = scenes_list[id];
    }

    current_state = State::main_loop_change_scene;

    return true;
}

bool Game::handle_scene_changes(){
    if(current_state == State::main_loop_change_scene){
        if(current_scene == NULL){
            return false;
        }else{
            Log::instance.info("Changing scene: '" + current_scene->name() + "'");

            if(next_scene != NULL){
                current_scene = next_scene;
            }else{
                //Somente na primeira vez.
                next_scene = current_scene;
            }

            if(last_current_scene)
                last_current_scene->shutdown();

            current_scene->init();

            current_state = State::main_loop;

        }
    }

    return true;
}
