#include "game.hpp"

#define FRAME 60
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
        if( startSDL() && createWindow() ){
            Log::instance.info("Iniciando o jogo");

            //Verifica se o jogo está sendo executado
            bool open_game = true;
            timer->start();
            //Cada cena tem um método init que inicializa a cena. No caso, estamos inicializando a cena atual.
            current_scene->init();

            while(open_game){
                SDL_Event evt;

                while( SDL_PollEvent(&evt) != 0 ){
                    if( evt.type == SDL_QUIT ){
                        open_game = false;
                    }

                    if( evt.type == SDL_KEYDOWN ){
                        switch (evt.key.keysym.sym) {
                            case SDLK_SPACE:
                                Log::instance.debug("teste teclado");
                                //Keyboard::isKeyDown(keycode::KEY_SPACE);
                                break;

                        }
                    }
                }
                current_scene->game_logic();
                //Limpa o Canvas visualizado pelo  usuário
                SDL_RenderClear(main_canvas);
                //Desenha no buffer secundário.
                current_scene->draw();
                //Exibe o Canvas secundário para o usuário
                SDL_RenderPresent(main_canvas);

                int frameTicks = timer->getTicks();
                if( frameTicks < FRAME )
                {
                    //                SDL_Delay( FRAME - frameTicks );
                }

            }

        }
        Log::instance.info("Desligando tudo");
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

        current_scene = scenes_list[id];
        return true;
    }
