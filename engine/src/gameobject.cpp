
/**
  \file gameobject.cpp
  This file contains the implementations of the gameobject member functions
*/

#include <assert.h>
#include "gameobject.hpp"
#include "components/image.hpp"
#include "components/animation.hpp"

using namespace engine;


/**
  Starts a new game object instance
  \return true if all components were succefully initialized
  \return false if some component receives a false initialization
*/

bool GameObject::init() {

    /**
        Iterates over the main components by initializing them
    */

    
    // Initialize gameobject's components
    for( index_component_pair id_componentlist: main_components ) {
        for ( Component * component: id_componentlist.second ) {
            assert(component != NULL);
            if( component->init() == true ) {
                // Do nothing
            } // If
            else { 
		Log::instance.error("The object with id: "+component->component_id+" has failed to initialize.");
                exit(-1);
            } // Else
        } // Internal for 
    } // External for -- After all of the components have been initialized



    return true;

}

/**
  Shuts the game object down, shutting down the components
  \return true if the gameObject's components were succefully shutted down
  \return false if some component is enabled but also shutted.
*/

bool GameObject::shutdown() {

    Log::instance.info("Shutdown game object");

    /**
        Iterates over the main components by shut them down.
    */


    // Shutdown gameobject's components
    for( index_component_pair id_componentList: main_components ) {
        for( Component * component:id_componentList.second ) {
            assert(component != NULL);
            
            if( component->state() != Component::State::enabled ||
                component->shutdown() == true ) {
                    // Do nothing
            } // if

            else {
	    	        Log::instance.error("The component " +component->component_id + " has failed to shutting down.");
                return false;
            } // else 
        } // internal for
    } // external for - after all of the gameobject's components have been shutdown

    return true;

}

/**
  Draws the components of the gameObject
  \return true
*/


void GameObject::draw_image_component() {

    /**
        Iterates over the main components by drawing their images
    */

    
    // draw main's components whose type are imageComponent
    for( Component * component:
         main_components[std::type_index(typeid(ImageComponent))]) {

            assert(component != NULL);

            /*
            If the component found with the enabled state, converts it to a
            component of the image and draws it on the screen.
            */

           // Only draws if the component state is enabled
           if( component->state() == Component::State::enabled ) {

               (dynamic_cast<ImageComponent *>(component))->draw();

               Log::instance.info(component->component_id+" had it image been drawed");

	         
           }
           else {
	            Log::instance.warning(component->component_id + " has not been drawed");
           }

    } // internal for
} // external for - when all of the main's image components have been drawn

void GameObject::draw_animation() {

    // draw the animation of the image components  
    for( Component * component:
        main_components[std::type_index(typeid(Animation))]) {
            assert(component != NULL);
            /*
            If the component found with the state enabled, convert it to a
            component of the image and draw on the screen.
            */

            if( component->state() == Component::State::enabled ) {
                (dynamic_cast<Animation *>(component))->draw();
	              Log::instance.info(component->component_id+" had it animation been drawed");
	    }
            else {
		            Log::instance.warning(component->component_id + " has not been drawed");
            }

    } // internal for 
} //  external for - reached when all of the main's image components have been drawn


bool GameObject::draw() {

    /**
        Draws gameobject's image and animation.
    */

    draw_animation();
    draw_image_component();

    return true;
}





    /*
        for(auto component: main_components[std::type_index(typeid(TextComponent))]){

        If the component found with the state enabled, convert it to a
        component of the image and draw on the screen.

        if(component->state() == Component::State::enabled)
        (dynamic_cast<TextComponent *>(component))->draw();
    }
    */

/**
  Adds a new component for the game object
  \param component the component object that will be added
*/

void GameObject::add_component(Component &component) {
    



    /**
        Adds logs entries concerning the components adding.
    */

    Log::instance.info("Adding component: '" +
                       component.component_id +
                       "' to game object: '" +
                       main_name +
                       "'.");

    /**
        Adds the component to the end of the list for the type of it.
    */


    main_components[std::type_index(typeid(component))] // Inserts a given component inside the current components list.
                   .push_back(&component);

    Log::instance.info(component.component_id + "has been added to list succesfuly");


}

/**
  Updates the current state of the gameObject
*/

void GameObject::update() {

    /**
        Iterates over main components by updating their state.
    */
  
    // updates the state of the main components
    for( index_component_pair id_componentlist: main_components ) {
        for( Component * component: id_componentlist.second ) {
            assert(component != NULL);
	          if( component->state() == Component::State::enabled) { // Only updates components whose state are enabled
                component->update();
	          } // if
            else {
		            Log::instance.warning(component->component_id + "has not been updated");
            } // else
        } // internal for
    } // external for - after all of the main components have been updated

}

/**
  Gets a component based on the string name
  \param name the name of the component
  \return returns a pointer to the component
  \return returns NULL if no component was found
*/

Component* GameObject::get_component(std::string name) {



    assert(!name.empty());

    /**
        Searches the main components for the component
        given its name.
    */
    
    // if the given string is not empty
    if( name != "" ) {

	   // Do nothing
	   
    }
    else {
	
	   Log::instance.error("String name is empty!");

	   return NULL;

    } 

    // searche on the main's components for the component of the given name
    for( index_component_pair id_componentList: main_components ) {
        for( Component * component:id_componentList.second ) {
            if( component->component_id == name ) {
                assert(component != NULL);
		            Log::instance.info("Component whose name is " + name + " has been found");
                return component;
            } // if
            else {
                // Do nothing
            } // else  
        } // internal for
    } // external for - after been searched on all components

    /**
        Adds an entry to log telling you that the given component was not found
        on the main game
    */

    Log::instance.warning("Component '" +
                          name +
                          "' not found in '" +
                          main_name +
                          "' gameobject.");

    return NULL;

}

/**
  Sets the state of the GameObject
  \param state the state to be setted
*/

void GameObject::setState(State state) {

    assert(state >= GameObject::State::enabled && state <= GameObject::State::invalid);

    main_state = state;

}

/*
    bool GameObject::collision( GameObject* object ) {

    SDL_Rect obj1;
    SDL_Rect obj2;
    SDL_Rect result;

    obj1.x = main_positionX;
    obj1.y = main_positionY;
    obj1.w = main_width;
    obj1.h = main_height;
    obj2.x = object->main_positionX;
    obj2.y = object->main_positionY;
    obj2.w = object->main_width;
    obj2.h = object->main_height;

    return SDL_IntersectRect( &obj1, &obj2, &result);

    }

    GameObject* GameObject::checkCollision() {

    Game::instance.current_scene->

    }
*/
