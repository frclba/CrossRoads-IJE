/**
    \file scene.cpp
    This file declares the Scene class
*/

#include "scene.hpp"

using namespace engine;

// Invalid game object definition

GameObject INVALID_GAME_OBJECT;


/**
    Add a new game objetc in scene.
    \param object new object to add
    \return true if the game object was added
    \retrun false if the game object already exists
*/
bool Scene::add_game_object(GameObject &object) {

    auto id = object.name();
    Log::instance.info("Adding GameObject '" + id + "' to scene '" + scene_name + "'.");


    /**
        Check if game_object exist and add to scene objects list.
    */
    if( scene_objects.find( id ) != scene_objects.end() ) {
        Log::instance.warning( "Game object: '" + id + "' já existe!" );
        return false;
    }
    else {
        scene_objects[id] = &object;
        return true;
    }

}

/**
    Take an object from the scene by id
    \param id required object identifier name
    \return game object if exists
    \return invalid game object is does not exists
*/
GameObject &Scene::get_game_object(const std::string &id) {

    if( scene_objects.find(id) != scene_objects.end() ) {
        return *scene_objects[id];
    }
    else {
        Log::instance.warning( "Não foi possível encontrar o GameObject '" + id +"'." );
        return INVALID_GAME_OBJECT;
    }

}

/**
    Remove an object from the scene by id
    \param id required object identifier name
    \return true if game object exists and is removed
    \return false if game object is does not exists
*/
bool Scene::remove_game_object(const std::string &id) {

    Log::instance.info("Removendo GameObject '" + id + "' da Scene.");

    if( scene_objects.find(id) != scene_objects.end() ) {
        scene_objects.erase( id );
        return true;
    }
    else {
        Log::instance.warning("Não foi possível encontrar o GameObject '" +
                              id + "'.");
        return false;
    }

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
    for( auto id_object: scene_objects ) {
        auto object = id_object.second;

        if( object->init() == true ) {
            // Do nothing
        }
        else {
            return false;
        }
    }

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
    for( auto id_object: scene_objects ) {
        auto object = id_object.second;

        if( object->state() != GameObject::State::enabled ||
            object->shutdown() != false ) {
            // Do nothing
        }
        else {
            return false;
        }

    }

    return true;

}

/**
    This method is reponsable for update the scene
    with objects
*/
void Scene::update() {

    for( auto id_object: scene_objects ) {
        auto object = id_object.second;

        if ( object->state() == GameObject::State::enabled ) {
            object->update();
        }
        else {
            // Do nothing
        }
    }

}

/**
    This method is responsible for the background
    and layers that make up the game design
    \return returns true when the scene is with layers and background.
*/
bool Scene::draw() {

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
    for( int cont = 0; cont < 4; cont++ ) {

        for( auto id_object: scene_objects ) {
            auto object = id_object.second;

            if( object -> m_layer != layers[cont] ||
                object -> state() != GameObject::State::enabled ||
                object -> draw() != false ) {
                    // Do nothing
            }
            else {
                return false;
            }
        }
    }

    return true;

}

/**
    Checks and lists the objects that will crash into the scene.
    \return list of colliding objects
*/

std::list <GameObject *> * Scene::get_collide_objects() {


    for( auto id_object: scene_objects ) {
        auto object = id_object.second;

        if( object -> state() == GameObject::State::enabled && object->m_collision == true ) {
            collide_objects.push_back(object);
        }
        else {
            // Do nothing
        }

    }

    return &collide_objects;

}

void Scene::clear_collide_objects() {

    collide_objects.clear();

}

void Scene::game_logic() {

}
