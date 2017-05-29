#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include <unordered_map>
#include <list>
#include "sdl2core.hpp"
#include "gameobject.hpp"

namespace engine{

    class Scene{
        public:
            enum class State{
                created,
                loaded,
                playing,
                invalid
            };

            //Sobrecarga do construtor para caso de criação de cenas sem parâmetros
            Scene() : Scene("", State::invalid){}

            Scene(std::string name, State _state = State::created)
            :scene_name(name), scene_state(_state){}

            virtual ~Scene(){}

            //Add and check if it already exists. If success, return true
           virtual bool add_game_object(GameObject &obj);

            //Search for a specific GameObject by ID
            GameObject &get_game_object(const std::string &id);

            //Erase GameObject, find it by ID and remove.
           virtual bool remove_game_object(const std::string &id);

            //Initialization of scene
            virtual bool init();

            //Shutdown of scene
            virtual bool shutdown();

            //Check on map and initialize each game object. Return true if success
            virtual bool draw();

           
            std::list<GameObject*> *get_collide_objects();
            void clear_collide_objects();
   //gamelogic
            virtual void game_logic();

            inline std::string name() const { return scene_name; }

            void update();
        protected:
            std::string scene_name;
            std::unordered_map <std::string, GameObject *> scene_objects;
            std::list <GameObject *> collide_objects;

            State scene_state;
    };

}

#endif
