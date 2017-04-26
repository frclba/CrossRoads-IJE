#ifndef __GAME_H__
#define __GAME_H__

#include <string>
#include <unordered_map>
#include <utility>

#include "sdl2core.hpp"

#include "Timer.hpp"
#include "scene.hpp"

namespace engine{

    class Game{
    public:
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

        SDL_Renderer* main_canvas;
        Timer *timer;

    private:
        Game()
            : main_canvas(NULL), main_name(""), main_window_size({0,0}),
            main_window(NULL),
            main_background_color({0xff, 0xff, 0xff, 0xff}),
            current_scene(NULL){};

        std::string main_name;

        std::pair<int,int> main_window_size;

        SDL_Window * main_window;

        SDL_Color main_background_color;

        std::unordered_map <std::string, Scene *> scenes_list;

        Scene *current_scene;
    };
}

#endif
