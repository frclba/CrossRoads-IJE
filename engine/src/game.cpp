
/**
  \file game.cpp
  this file contain methods related to the game object
*/

#include "game.hpp"

#define FRAME 60.0

using namespace engine;

Game Game::instance;


/**
  Sets the name and window size of the game
  \param name set the name of the game
  \param window_size sets the size of the window
*/

void Game::set_properties(std::string name, std::pair<int, int> window_size) {

    main_name = name;
    main_window_size = window_size;

}



/**
  Initializes the SDL configuration of the game
  \return true if all sdl units were correctly initialized
  \return false if something went wrong on sdl inialization
*/

bool Game::start_sdl() {

    Log::instance.info("Iniciando video e audio");

    if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0 ) {
        Log::instance.error( "Error ao inicializar video ou audio ou joystick" );
        return false;
    }
    else {
        // Do nothing
    }

    Log::instance.info("Iniciando Imagem");

    //Caso forem ser usados outros tipos de imagem, inserir as flags aqui

    int img_flags = IMG_INIT_PNG;

    if( !(IMG_Init( img_flags ) & img_flags) ) {
        Log::instance.error( "Erro ao inicializar imagens !" );
        return false;
    }
    else {
        // Do nothing
    }

    if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1 ) {
        Log::instance.error("Erro ao inicializar mixer");
        return false;
    }
    else {
        // Do nothing
    }

    timer = new Timer();
    mouse = new Mouse();
    keyboard = new Keyboard();
    collision_manager = new CollisionManager();

    if( SDL_NumJoysticks() > 0 ) {
        //Load joystick

        g_game_controller = SDL_JoystickOpen( 0 );

        if( g_game_controller == NULL ) {
            //printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
        }
        else {
            // Do nothing
        }
    }

    else {
        //printf( "Warning: No joysticks connected!\n" );
    }

    return true;

}


/**
  creates a new instance of a game window
  \return return true if the window was succefully created
  \return false if there is neighter a window or a canvas initialized
*/

bool Game::create_window() {

    Log::instance.info("Criando janela");

    main_window = SDL_CreateWindow(
        main_name.c_str(),          //Titulo
        SDL_WINDOWPOS_CENTERED,     //Posicao em X
        SDL_WINDOWPOS_CENTERED,     //Posicao em Y
        main_window_size.first,     //Width
        main_window_size.second,    //Height
        SDL_WINDOW_SHOWN            //Window flags
    );

    if( main_window == NULL ) {
        Log::instance.error("Falha ao criar janela");
        return false;
    }
    else {
        // Do noting
    }

    main_canvas = SDL_CreateRenderer(
        main_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if( main_canvas == NULL ) {
        Log::instance.error("Falha ao criar renderizador");
        return false;
    }
    else {
        // Do nothing
    }

    SDL_SetRenderDrawColor(
        main_canvas,
        main_background_color.r,
        main_background_color.g,
        main_background_color.b,
        main_background_color.a
    );

    return true;

}



void Game::destroy_window() {

    SDL_DestroyRenderer(main_canvas);
    main_canvas = NULL;

    SDL_DestroyWindow(main_window);
    main_window = NULL;

}


/**
  nulify all SDL units
*/

void Game::off_sdl() {

    SDL_JoystickClose(g_game_controller);
    g_game_controller = NULL;
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

}



/**
  creates a new game instance
*/

void Game::run() {

    current_state = State::init;

    if( start_sdl() && create_window() ) {
        Log::instance.info("Iniciando o jogo");

        current_state = State::main_loop;

        unsigned int frame_time = 1000.0 / FRAME;

        timer -> start();

        if( current_scene != NULL ) {
            current_state = State::main_loop_change_scene;
        }
        else {
            // Do nothing
        }

        while( current_state != State::exit_loop ) {
            if( handle_scene_changes() == false ) {
                break;
            }
            else {
                // Do nothing
            }

            SDL_Event evt;

            //get mouse position
            mouse -> set_position();

            while( SDL_PollEvent(&evt) != 0 ) {
                if( evt.type == SDL_QUIT ) {
                    current_state = State::exit_loop;
                }
                else {
                    // Do nothing
                }

                keyboard -> setKeys(&evt);

                if( evt.type == SDL_KEYDOWN ) {
                    switch( evt.key.keysym.sym ) {
                        case SDLK_SPACE:

                        //Log::instance.debug("teste teclado");

                        //Keyboard::isKeyDown(keycode::KEY_SPACE);

                        break;
                    }
                }
                else {
                    // Do nothing
                }
            }

            //	current_scene->get_collide_objects();

            collision_manager -> getCollisions(current_scene -> get_collide_objects());
            current_scene -> update();
            current_scene -> game_logic();

            //Limpa o Canvas visualizado pelo  usuário

            SDL_RenderClear(main_canvas);

            //Desenha no buffer secundário.

            current_scene -> draw();

            //Exibe o Canvas secundário para o usuário

            SDL_RenderPresent(main_canvas);

            if( frame_time > timer-> get_elapseTime() ) {
                SDL_Delay(timer -> get_elapseTime());
            }
            else {
                // Do nothing
            }

            keyboard -> clearKeyboard();
            current_scene -> clear_collide_objects();
            timer -> set_TimeStep();
        }

        Log::instance.info( "Cleaning scene..." );
        if( !current_scene ) {
            // Do nothing
        }
        else {
            current_scene -> shutdown();
        }
    }

    Log::instance.info("Desligando tudo");
    current_state = State::shutdown;
    destroy_window();
    off_sdl();
}


/**
  adds a scene for the current game
  \param scene the scene object that will be added
  \return true if the scene was succefully added to the scene list of the game
  \return false if the scene object was already loaded
*/

bool Game::add_scene(Scene &scene) {
    //Isso faz o id ser o name.
    auto id = scene.name();
    Log::instance.info("Adding Scene: '" + id + "' to Scenes List.");

    //A scene desejada sempre tem que ser a ultima. Se não for, vai ser adicionada novamente.
    if( scenes_list.find(id) != scenes_list.end() ) {
      Log::instance.warning("The scene '"+ id +"' is already loaded!");
      return false;
    }
    else {
        // Do nothing
    }

    scenes_list[id] = &scene;

    if( current_scene == NULL ) {
        change_scene(id);
    }
    else {
        // Do nothing
    }

    return true;
}


/**
  changes the actual scene for a new one specified by the id parameter
  \param id id of the new current scene
  \return true if the scene was succefully changed
  \return false if the scene was already been loaded
*/

bool Game::change_scene(const std::string &id) {

    if( scenes_list.find(id) != scenes_list.end() ) {
        // Do nothing
    }
    else {
        return false;
    }

    last_current_scene = current_scene;

    // current_scene = scenes_list[id];
    if(next_scene != NULL){
        printf("Pŕoxima cena que foi setada\n");
        next_scene = scenes_list[id];
    }
    else {
        //Quando for rodado a primeira vez.
        current_scene = scenes_list[id];
    }

    current_state = State::main_loop_change_scene;

    return true;
}

/**
  updates the actual scene scheme
  \return true if the current_scene was succefully updated
  \return false if the current_scene is empty
*/
bool Game::handle_scene_changes() {

    if(current_state == State::main_loop_change_scene) {
        if(current_scene == NULL) {
            return false;
        }
        else {
            Log::instance.info("Changing scene: '" + current_scene->name() + "'");

            if(next_scene != NULL){
                current_scene = next_scene;
            }
            else {
                //Somente na primeira vez.
              next_scene = current_scene;
            }

        if(last_current_scene) {
            last_current_scene->shutdown();
        }
        else {
            // Do nothing
        }

        current_scene->init();

        current_state = State::main_loop;

        }
  }

return true;

}
