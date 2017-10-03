/**
    \file component.hpp
    This file declares game_object and Component class
*/

#ifndef FOO_BAR_ENGINE_COMPONENTS_COMPONENT_H_
#define FOO_BAR_ENGINE_COMPONENTS_COMPONENT_H_

namespace engine {

    /// Class to control game objects
    /**
        \class game_object
        This class is responsible to control game objects
    */
    class GameObject;

    /// Class to control game objects
    /**
        \class game_object
        This class is responsible to control game objects, but in this file
        this class is here empty just to not have problems of cyclic imports
    */
    class Component {

        public:
            /// Class to control states
            /**
                \class State
                This class is responsible to control all states of game
            */
            enum class State{

                enabled,
                disabled,
                invalid

            };

            /*
                Overhead of build for created components without parameters
                being invalid.
            */
            Component(): main_state(State::invalid), _main_game_object(NULL) {

                // Default function call.

            }

            /**
                Construct method for a game_object already instantiated
                \param[in] game_object reference address to game_object
                \param[in] name string
                \result component_id receive name as Component identifier
                \result main_state set as enabled enum value
                \result _main_game_object ponteir receive game_object reference
            */
            Component(GameObject &game_object, std::string name) : 
                      component_id(name), main_state(State::enabled),
                      _main_game_object(&game_object) {

                // Default function call.

            }

            /**
                This method is an empty constructor
            */
            virtual ~Component() {

                // Default function call.

            };

            /**
                This method initialize components
            */
            virtual bool init() { 

                return true;

            }

            /**
                This method finish components
            */
            virtual bool shutdown() {

                return true;

            }

            /**
                This is an empty method
            */
            virtual void update() {

                // Default function call.

            }

            /**
                This method return actual state of game
            */
            inline State state() { 

                return main_state;

            }

            /**
                This method enable actual state
            */
            inline void enable() {

                main_state = State::enabled;

            }

            /**
                This method disable actual state
            */
            inline void disable() { 

                main_state = State::disabled;

            }

            /** 
                Save id of components. 
            */
            std::string component_id = "";

            /** 
                Control actual state of game. 
            */
            State main_state;

        protected:
            /*
                Keep a reference of the game object which it
                belongs
            */
            GameObject* _main_game_object = NULL;

    };

}

#endif // FOO_BAR_ENGINE_COMPONENTS_COMPONENT_H_