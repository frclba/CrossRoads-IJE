/**
    \file component.hpp
    This file declares GameObject and Component class
*/
#ifndef FOO_BAR_ENGINE_COMPONENTS_COMPONENT_H_
#define FOO_BAR_ENGINE_COMPONENTS_COMPONENT_H_

namespace engine {

    /*
        Define the class gameobject as empty here to haven't any problem of
        cyclic import.
    */

    /// Class to control game objects
    /**
        \class GameObject
        This class is responsible to control game objects
    */
    class GameObject;

    /// Class to control game objects
    /**
        \class GameObject
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

            }

            Component(GameObject &gameObject, std::string name)
                : component_id(name), main_state(State::enabled),
                _main_game_object(&gameObject) {

            }

            /**
                This method is an empty constructor
            */
            virtual ~Component() {

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

            std::string component_id;

            State main_state;

        protected:

            /*
                The component keeps a reference of the game object which it
                belongs
            */

            GameObject* _main_game_object;
            
    };

}

#endif // FOO_BAR_ENGINE_COMPONENTS_COMPONENT_H_