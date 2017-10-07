/**
  \file game.hpp
  this file contain the namespace engine, who defines the game engine class
*/

#ifndef __GAME_H__
#define __GAME_H__

#include <string>
#include <unordered_map>
#include <utility>
#include <list>

#include "sdl2core.hpp"

#include "Timer.hpp"
#include "scene.hpp"
#include "mouse.hpp"
#include "Keyboard.hpp"
#include "collision_manager.hpp"

enum class State{
    created,
    init,
    main_loop,
    main_loop_change_scene,
    exit_loop,
    pause,
    shutdown
};

namespace engine {



    /// Class for managing the game object properties
    /**
    \class Game
    This class has features for managing some of game properties
    such as SDL configuration  and scenes handling.
    */

    class Game {

    public:
        //Creating a single and unique game instance.
        static Game instance;

        //Define some class variables like name and window_size
        void set_properties(std::string name, std::pair<int,int> window_size);

        //Game loop
        void run();

        //Inicializa SDL
        bool start_sdl();

        //Cria janela
        bool create_window();

        //Destroi janela
        void destroy_window();

        //Desliga SDL
        void off_sdl();

        //Adiciona nova cena na lista de cenas
        bool add_scene(Scene &scene);

        //Muda a cena que está acontecendo
        bool change_scene(const std::string &id);

        bool handle_scene_changes();

        SDL_Renderer* main_canvas;

        Timer *timer;
        Mouse *mouse;
        Keyboard* keyboard;
        CollisionManager* collision_manager;
        Scene* current_scene;

    private:
        Game()
            : main_canvas(NULL), current_scene(NULL), main_name(""),
            main_window_size({0,0}), main_window(NULL),
            main_background_color({0xff, 0xff, 0xff, 0xff}),
            current_state(State::created), last_current_scene(NULL){};

        std::string main_name;
        std::pair<int,int> main_window_size;
        SDL_Window* main_window;
        SDL_Color main_background_color;
        State current_state;
        SDL_Joystick* g_game_controller = NULL;

        Scene *last_current_scene;
        Scene *next_scene;

        std::unordered_map <std::string, Scene *> scenes_list;
    };
}

#endif
