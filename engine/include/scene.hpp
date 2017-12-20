/**
    \file scene.hpp
    This file declares the Scene class
*/
#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include <unordered_map>
#include <list>
#include <assert.h>

#include "sdl2core.hpp"
#include "gameobject.hpp"

namespace engine {

    /// Class for control of game Scene
    /**
        \class Scene
        This class is responsible for initializing the game scene
    */
    class Scene {

        public:
            enum class State {
                created,
                loaded,
                playing,
                invalid
            };

            // Overloading the constructor for creating scenes without parameters

            Scene() : Scene( "", State::invalid ) {

            }

            Scene( std::string name, State _state = State::created )
            :scene_name( name ), scene_state( _state ) {

            }

            virtual ~Scene() {

            }

            // Add and check if it already exists. If success, return true

            virtual bool add_game_object( GameObject &object );

            // Search for a specific GameObject by ID

            GameObject &get_game_object( const std::string &id );

            // Erase GameObject, find it by ID and remove.

            virtual bool remove_game_object( const std::string &id );

            std::list<GameObject*> *get_collide_objects();

            void clear_collide_objects();

            // Initialization of scene

            virtual bool init();

            // Shutdown of scene

            virtual bool shutdown();

            // Check on map and initialize each game object. Return true if success

            virtual bool draw();

            // gamelogic

            virtual void game_logic();

            inline std::string name() const {

                return scene_name;

            }

            void update();

        protected:
            std::string scene_name;
            std::unordered_map <std::string, GameObject *> scene_objects;
            std::list <GameObject *> collide_objects;

            State scene_state;

    };

}

#endif
