/**
    \file scene.cpp
    This file declares the Scene class
*/

#include "scene.hpp"

using namespace engine;

// Invalid game object definition

GameObject INVALID_GAME_OBJECT;


/**
    Add a new game objectetc in scene.
    \param object new object to add
    \return true if the game object was added
    \retrun false if the game object already exists
*/
bool Scene::add_game_object(GameObject &object) {

    auto id = object.name();

    Log::instance.info("Adding GameObject '" + id + "' to scene '" + scene_name + "'.");
    // checks if the given string is not empty
    if( id != "" ) {

        /**
            Check if game_object exist and add to scene objects list.
        */
        if( scene_objects.find( id ) == scene_objects.end() ) {
            scene_objects[id] = &object;
            return true;
        }
        else {
            Log::instance.warning( "Game object: '" + id + "' já existe!" );
            return false;
        }
    } else {
        Log::instance.warning( "Could not add scene, Scene id is empty.");
        return false;
    }
}

/**
    Take an object from the scene by id
    \param id required object identifier name
    \return game object if exists
    \return invalid game object is does not exists
*/
GameObject &Scene::get_game_object(const std::string &id) {

    Log::instance.info("Get GameObject '" + id + "' in Scene.");
    // checks if the given string is not empty
    if( id != "" ) {
         // verifies if the component ofthe  given string was found and then returns it
         if( scene_objects.find(id) != scene_objects.end() ) {
             return *scene_objects[id];
         } // if 
         else {
             Log::instance.warning( "Não foi possível encontrar o GameObject '" + id +"'." );
             return INVALID_GAME_OBJECT;
         } // else
    } else {
        Log::instance.warning( "Could not find scene, Scene id is empty.");
        return INVALID_GAME_OBJECT;
    } // else

}

/**
    Remove an object from the scene by id
    \param id required object identifier name
    \return true if game object exists and is removed
    \return false if game object is does not exists
*/
bool Scene::remove_game_object(const std::string &id) {

    Log::instance.info("Removendo GameObject '" + id + "' da Scene.");
    // checks if the given string was not empty
    if( id != "" ) {
        // if the component of the given string was found
        if( scene_objects.find(id) != scene_objects.end() ) {
            scene_objects.erase(id);
            return true;
        } // if
        else {
            Log::instance.warning("Não foi possível encontrar o GameObject '" +
                                  id + "'.");
            return false;
        } // else
    } else {
        Log::instance.warning( "Could not remove scene, Scene id is empty.");
        return false;
    } // else

}

/**
    This method initiates the scene in the game
    \return return a true value when the scene is active
*/
bool Scene::init() {

    Log::instance.info("Inicializando cena '" + scene_name + "'.");


    /**
        Initializes all objects in the scene.
    */

    // initializes all objects by iterating over the scene objects.
    for( auto id_object: scene_objects ) {
        auto object = id_object.second;
        // checks if the given object was initialized correctly 
        if( !object->init() ) {
            Log::instance.error(object->name() + "could not initialize");
            return false;
        } // if 
        else {
            // Do nothing
        } 
    } // for -- reached only if all objects on the scene objects were correcly initialized.

    return true;

}

/**
    This method closes the scene in the game
    \return return a true value when the scene is not active
*/
bool Scene::shutdown() {

    Log::instance.info("Destruindo cena '" + scene_name + "'.");

    /**
        Disables all objects in the scene.
    */

    // shuts down the objects on the scene objects 
    for( auto id_object: scene_objects ) {
        auto object = id_object.second;
        // only shutdown the component if he is not enabled
        if( object->state() != GameObject::State::enabled ||
            object->shutdown() != false ) {
            // Do nothing
        }
        else {
            Log::instance.error("Failed to shut down scene object:" + object->name());
            return false;
        }

    } // for - only reached if all the objects on the scene objects were or not enabled or were shuted down.

    return true;

}

/**
    This method is reponsable for update the scene
    with objects
*/
void Scene::update() {

    Log::instance.info("Update scene objects");
    
    // updates the objects on the scene_objects   
    for( auto id_object: scene_objects ) {
        auto object = id_object.second;
        // only updates if the object state is enabled.
        if ( object->state() == GameObject::State::enabled ) {
            object->update();
        }
        else {
            // Do nothing
        }
    } // for - reached when checked all objects on the scene objects.

}

/**
    This method is responsible for the background
    and layers that make up the game design
    \return returns true when the scene is with layers and background.
*/
bool Scene::draw() {

    Log::instance.info("Draw scene objects in each layer");

    /**
        Sets the scene layers.
    */
    GameObject::Layer layers[] = {
        GameObject::Layer::background,
        GameObject::Layer::layer1,
        GameObject::Layer::layer2,
        GameObject::Layer::layer3
    };

    /**
        Draw the object for each layer.
    */

    // draw the objects in one of the four layers
    for( int cont = 0; cont < 4; cont++ ) {
        for( auto id_object: scene_objects ) {
            auto object = id_object.second;
            if( object -> m_layer != layers[cont] ||
                object -> state() != GameObject::State::enabled ||
                object -> draw() != false ) {
                    // Do nothing
            } 
            else {
                Log::instance.warning("could not draw object: " + object->name());
                return false;
            }
        } // internal for
    }  // external for - reached only if all of the objects on the scene_objcts were correcly drawn.

    return true;

}

/**
    Checks and lists the objects that will crash into the scene.
    \return list of colliding objects
*/

std::list <GameObject *> * Scene::get_collide_objects() {

    Log::instance.info("List collided objects in " + scene_name);

    // identifies and return the collided objects on the scene objects.
    for( auto id_object: scene_objects ) {
        auto object = id_object.second;
        // if the state of the given object is enabled and it has collision.
        if( object->state() == GameObject::State::enabled && object->m_collision == true ) {
            Log::instance.info("Colide object: " + object->name());
            collide_objects.push_back(object);
        } // if
        else {
            // Do nothing
        } // else

    } // for 

    return &collide_objects;

}

void Scene::clear_collide_objects() {

    collide_objects.clear();

}

void Scene::game_logic() {

}
