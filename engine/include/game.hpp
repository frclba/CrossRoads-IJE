#ifndef __GAME_H__
#define __GAME_H__

#include <string>
#include <unordered_map>
#include <utility>

#include "sdl2core.hpp"

#include "Timer.hpp"
#include "scene.hpp"
#include "mouse.hpp"

namespace engine{

    class Game{
    public:
        enum class State{
            created,
            init,
            main_loop,
            main_loop_change_scene,
            exit_loop,
            pause,
            shutdown
        };

        //Creating a single and unique game instance.
        static Game instance;

        //Define some class variables like name and window_size
        void set_properties(std::string name, std::pair<int,int> window_size);

        //Game loop
        void run();

        //Inicializa SDL
        bool startSDL();

        //Cria janela
        bool createWindow();

        //Destroi janela
        void destroyWindow();

        //Desliga SDL
        void offSDL();

        //Adiciona nova cena na lista de cenas
        bool add_scene(Scene &scene);

        //Muda a cena que está acontecendo
        bool change_scene(const std::string &id);

        bool handle_scene_changes();

        SDL_Renderer* main_canvas;

        Timer *timer;
        Mouse *mouse;

    private:
        Game()
            : main_canvas(NULL), main_name(""),
            main_window_size({0,0}), main_window(NULL),
            main_background_color({0xff, 0xff, 0xff, 0xff}),
            current_scene(NULL), current_state(State::created), last_current_scene(NULL){};

        std::string main_name;
        std::pair<int,int> main_window_size;
        SDL_Window * main_window;
        SDL_Color main_background_color;
        State current_state;
        Scene *current_scene;

        //Necessário armazenar a última cena para desalocar memória dela na troca, caso necessário.
        Scene *last_current_scene;
        std::unordered_map <std::string, Scene *> scenes_list;
    };
}

#endif
