
/**
  \file game.cpp
  this file contain methods related to the game object
*/

#include "game.hpp"

#define FRAME 60.0

using namespace engine;

Game Game::instance;

/**
  creates a new game instance
*/

bool Game::run() {

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
            Log::instance.warning("There is no current scene");
        }

        while( current_state != State::exit_loop ) {
            if( handle_scene_changes() ) {
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

                /// \note Clears the Canvas viewed by the user
                SDL_RenderClear(main_canvas);

                /// \note Draw in the secondary buffer
                current_scene -> draw();

                /// \note Displays the Secondary Canvas for the user
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
            } else {
                break;
            }
        }

        Log::instance.info( "Cleaning scene..." );
        if( current_scene ) {
            current_scene -> shutdown();
        }
        else {
            // Do nothing
        }

        Log::instance.info("Game shutdown");
        current_state = State::shutdown;
        destroy_window();
        off_sdl();

        return true;
    } else {
        Log::instance.error("Failied to run game instance");
        return false;
    }

}

/**
  Sets the name and window size of the game
  \param name set the name of the game
  \param window_size sets the size of the window
*/
int Game::set_properties(std::string name, std::pair<int, int> window_size) {

    /**
        Check if name is valid
    */
    if(name != "") {
      main_name = name;
      main_window_size = window_size;
      return 1;
    } else {
      return -2;
    }
}



/**
  Initializes the SDL configuration of the game
  \return true if all sdl units were correctly initialized
  \return false if something went wrong on sdl inialization
*/


bool Game::initialize_sdl_components() {

    Log::instance.info("Inicializando componentes SDL");

    /**
        Verify that the SDL library is successfully initialized.
    */
    if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) == 0 ) {
        return true;
    }
    else {
        Log::instance.error( "Error ao inicializar video ou audio ou joystick" );
        return false;
    }

}

bool Game::initialize_imgs() {

    Log::instance.info("Iniciando Imagem");

    int img_flags = IMG_INIT_PNG;

    /**
        Make sure image sdl initializes support for png files.
    */
    if( (IMG_Init( img_flags ) & img_flags) ) {
        return true;
    }
    else {
        Log::instance.error( "Erro ao inicializar imagens !" );
        return false;
    }

}


bool Game::initialize_mixer() {

    Log::instance.info("Iniciando Mixer");

    /**
        Check Mix_OpenAudio function return
    */
    if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != -1 ) {
        return true;
    }
    else {
        Log::instance.error("Erro ao inicializar mixer");
        return false;
    }

}

bool Game::start_sdl() {

    /**
        Verifies that all components, images, and audios have been initialized.
    */
    if( initialize_sdl_components() &&
        initialize_imgs() &&
        initialize_mixer() ) {
            // Do nothing
    }
    else {
      Log::instance.error("Failed to initialize SDL elements");
      return false;
    }


    timer = new Timer();
    mouse = new Mouse();
    keyboard = new Keyboard();
    collision_manager = new CollisionManager();

    /**
        Check if the player is using a joysticker as a control.
    */
    if( SDL_NumJoysticks() > 0 ) {
        //Load joystick

        g_game_controller = SDL_JoystickOpen( 0 );

        if( g_game_controller == NULL ) {
            std::string sdl_error = SDL_GetError();
            Log::instance.warning("Unable to open game controller! SDL Error: " + sdl_error );
        }
        else {
            // Do nothing
        }
    }

    else {
        Log::instance.warning("No joysticks connected");
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

    /**
        Checks if main_windown has been initialized.
    */
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

    /**
        Checks if main_canvas has been initialized.
    */
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
  adds a scene for the current game
  \param scene the scene object that will be added
  \return true if the scene was succefully added to the scene list of the game
  \return false if the scene object was already loaded
*/

bool Game::add_scene(Scene &scene) {

    /// \note Use the name as id
    auto id = scene.name();

    /**
        Check if id is valid.
    */
    if(id != "") {
      Log::instance.info("Adding Scene: '" + id + "' to Scenes List.");
    } else {
      Log::instance.info("Invalid id to scene");
      return false;
    }

    /**
        \note The desired scene always has to be the last. If it is not, it will be added again.
    */
    if( scenes_list.find(id) != scenes_list.end() ) {
      Log::instance.warning("The scene '"+ id +"' is already loaded!");
      return false;
    }
    else {
        // Do nothing
    }

    scenes_list[id] = &scene;

    /**
        Change scene if there aren't current scene.
    */
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

    /**
        Check if id is valid.
    */
    if(id == "") {
        Log::instance.error("Invalid id in change scene");
    } else {
      // Do nothing
    }

    /**
        The execute function fails if there is no ID in the scene list.
    */
    if( scenes_list.find(id) == scenes_list.end() ) {
        Log::instance.warning(id + "scene not found");
        return false;
    }
    else {
        // Do nothing
    }

    last_current_scene = current_scene;

    /**
        Switch to the next scene. If there is no next scene,
        switch to the scene with the given id.
    */
    if(next_scene != NULL){
        Log::instance.info("Pŕoxima cena que foi setada");
        next_scene = scenes_list[id];
    }
    else {
        /// \note For the first time the code is executed
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

    /**
        Checks if scene switching is enabled.
    */
    if(current_state == State::main_loop_change_scene) {

        /**
            Checks if there is current scene
        */
        if(current_scene == NULL) {
            Log::instance.info("Current scene not set");
            return false;
        }
        else {
            Log::instance.info("Changing scene: '" + current_scene->name() + "'");

            /**
                Update next scene
            */
            if(next_scene != NULL){
                current_scene = next_scene;
            }
            else {
              /// \note For the first time the code is executed
              next_scene = current_scene;
            }

        /**
            Shutdown current scene if the player orders to leave the game.
        */
        if(last_current_scene) {
            Log::instance.info("Last scene: '" + current_scene->name() + "'");
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
