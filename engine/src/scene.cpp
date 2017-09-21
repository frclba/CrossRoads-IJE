/**
    \file scene.cpp
    This file declares the Scene class
*/
#include "scene.hpp"

using namespace engine;

// Invalid game object definition

GameObject INVALID_GAME_OBJECT;

/**
    This method adds a game object in the scene
    \param &obj is a input parameter that represents an address of game object
    \return returns a true value when a non-existent object to enter the scene
*/
bool Scene::add_game_object( GameObject &obj ) {

    auto id = obj.name();
    Log::instance.info( "Adding GameObject '" + id + "' to scene '" + scene_name + "'." );

    // Iterating map to see if that game object already exists in it

    if( scene_objects.find( id ) != scene_objects.end() ) {
        Log::instance.warning( "Game object: '" + id + "' já existe!" );
        return false;
    }

    scene_objects[id] = &obj;
    return true;

}

GameObject &Scene::get_game_object( const std::string &id ) {

    if( scene_objects.find( id ) == scene_objects.end() ) {
        Log::instance.warning( "Não foi possível encontrar o GameObject '" + id +"'." );
        return INVALID_GAME_OBJECT;
    }

    return *scene_objects[id];

}

bool Scene::remove_game_object( const std::string &id ) {

    Log::instance.info( "Removendo GameObject '" + id + "' da Scene." );

    if( scene_objects.find(id) == scene_objects.end() ) {
        Log::instance.warning(
            "Não foi possível encontrar o GameObject '" + id + "'."
        );

        return false;
    }

    scene_objects.erase( id );

    return true;

}

/**
    This method initiates the scene in the game
    \return return a true value when the scene is active
*/
bool Scene::init() {

    Log::instance.info( "Inicializando cena '" + scene_name + "'." );

    // Iterating the map and initializing each of the game objects.

    for( auto id_obj: scene_objects ) {
        auto obj = id_obj.second;

        if( obj -> init() == false ) {
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

    Log::instance.info( "Destruindo cena '" + scene_name + "'." );

    // Iterating the map and initializing each of the game objects.

    for( auto id_obj: scene_objects ) {
        auto obj = id_obj.second;

        if( obj -> state() == GameObject::State::enabled &&
        obj -> shutdown() == false )

        return false;

    }

    return true;
}

/**
    This method is reponsable for update the scene
    with objects
*/
void Scene::update() {

    for( auto id_obj: scene_objects ) {
        auto obj = id_obj.second;

        if( obj -> state() == GameObject::State::enabled ) {
            obj -> update();
        }
    }

}

/**
    This method is responsible for the background 
    and layers that make up the game design
    \return returns true when the scene is with layers and background.
*/
bool Scene::draw() {

    GameObject::Layer layers[] = {
        GameObject::Layer::background,
        GameObject::Layer::layer1,
        GameObject::Layer::layer2,
        GameObject::Layer::layer3
    };

    // Iterating the map and initializing each of the game objects.

    for( int cont = 0; cont < 4; cont++ ) {

        for( auto id_obj: scene_objects ) {
            auto obj = id_obj.second;

            if( obj -> m_layer == layers[cont] &&
                obj -> state() == GameObject::State::enabled &&
                obj -> draw() == false ) {
                return false;
            }
        }
    }

    return true;

}

std::list <GameObject *> * Scene::get_collide_objects() {

    // Iterating the map and initializing each of the game objects.

    for( auto id_obj: scene_objects ) {
        auto obj = id_obj.second;

        if( obj -> state() == GameObject::State::enabled && obj -> m_collision == true ) {
            collide_objects.push_back( obj );
        }

    }

    return &collide_objects;

}

/**
    This method is reponsable for clear collide of objects 
    in the scene
*/
void Scene::clear_collide_objects() {

    collide_objects.clear();

}

/**
    This method is reponsable for game logic 
    in the scene
*/
void Scene::game_logic() {
    
}
