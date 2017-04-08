#include "game.hpp"

#define FRAME 60
using namespace engine;

Game Game::instance;
void Game::set_properties(std::string name, std::pair<int, int> window_size){
    main_name = name;
    main_window_size = window_size;
}

bool Game::startSDL(){

    //log.info("Iniciando video e audio\n");

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        //log.error("Error ao inicializar video ou audio\n");
        return false;
    }

    //log.info("Iniciando Imagem\n");
    int img_flags = IMG_INIT_PNG; //Caso forem ser usados outros tipos de imagem, inserir as flags aqui
    if(!(IMG_Init(img_flags) & img_flags)){
        //log.error("Erro ao inicializar imagens !\n");
        return false;
    }
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
        //log.error("Erro ao inicializar mixer");
        return false;
    }

    timer = new Timer();

    return true;

}

bool Game::createWindow(){
    //log.info("Criando janela");

    main_window = SDL_CreateWindow( main_name.c_str(),          //Titulo
                                    SDL_WINDOWPOS_CENTERED,     //Posicao em X
                                    SDL_WINDOWPOS_CENTERED,     //Posicao em Y
                                    main_window_size.first,     //Width
                                    main_window_size.second,    //Height
                                    SDL_WINDOW_SHOWN );         //Window flags
    if( main_window == NULL ){
        //log.error("Falha ao criar janela\n");
        return false;
    }

    main_canvas = SDL_CreateRenderer( main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    if ( main_canvas == NULL ){
        //log.error("Falha ao criar renderizador\n");
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
            //log.info("Iniciando o jogo\n");

            //Verifica se o jogo está sendo executado
            bool open_game = true;
            timer->start();
            //Cada cena tem um método init que inicializa a cena. No caso, estamos inicializando a cena atual.
            current_scene->init(main_canvas);

            while(open_game){
                SDL_Event evt;

                while( SDL_PollEvent(&evt) != 0 ){
                    if( evt.type == SDL_QUIT )
                    open_game = false;
                }
                //Limpa o Canvas visualizado pelo  usuário
                SDL_RenderClear(main_canvas);
                //Desenha no buffer secundário.
                current_scene->draw(main_canvas,timer);
                //Exibe o Canvas secundário para o usuário
                SDL_RenderPresent(main_canvas);

                int frameTicks = timer->getTicks();
                if( frameTicks < FRAME )
                {
                    //                SDL_Delay( FRAME - frameTicks );
                }

            }

            //log.info("Desligando tudo\n");
        }

        destroyWindow();
        offSDL();
    }

    bool Game::add_scene(Scene &scene){
        //Isso faz o id ser o name.
        auto id = scene.name();
        //log.info("Adicionando cena\n");

        //A scene desejada sempre tem que ser a ultima. Se não for, vai ser adicionada novamente.
        if( scenes_list.find(id) != scenes_list.end() ){
            //log.warning("Essa cena já está carregada !\n");
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
