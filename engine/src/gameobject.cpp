#include "gameobject.hpp"
#include "components/image.hpp"
#include "components/animation.hpp"


using namespace engine;

bool GameObject::init(){
    Log::instance.info("Initilizing GameObject '" + main_name + "'.");
    //Iterando o mapa de componentes, passando por cada tipo de componente.
    for(auto id_componentList: main_components){
        //Iterando a lista de componentes do tipo encontrado.
        for(auto component:id_componentList.second){
            if(component->state() == Component::State::enabled && component->init() == false)
                return false;
        }
    }

    return true;
}

bool GameObject::shutdown(){
    Log::instance.info("Shutdown game object");

    //Iterando o mapa de componentes, passando por cada tipo de componente.
    for(auto id_componentList: main_components){
        //Iterando a lista de componentes do tipo encontrado.
        for(auto component:id_componentList.second){
            if(component->state() == Component::State::enabled && component->shutdown() == false)
                return false;
        }
    }

    return true;
}

bool GameObject::draw(){
    //Procurando no mapa os componentes do tipo ImageComponent
    for(auto component: main_components[std::type_index(typeid(ImageComponent))]){
        /*Caso o componente encontrado esteja com estado habilitado, converte ele para um componente de imagem
        e o desenha na tela*/
        if(component->state() == Component::State::enabled)
            (dynamic_cast<ImageComponent *>(component))->draw();
    }

    for(auto component: main_components[std::type_index(typeid(Animation))]){
        /*Caso o componente encontrado esteja com estado habilitado, converte ele para um componente de imagem
          e o desenha na tela*/
        if(component->state() == Component::State::enabled)
            (dynamic_cast<Animation *>(component))->draw();
    }

    //
    // for(auto component: main_components[std::type_index(typeid(TextComponent))]){
    //     /*Caso o componente encontrado esteja com estado habilitado, converte ele para um componente de texto
    //     e o desenha na tela*/
    //     if(component->state() == Component::State::enabled)
    //         (dynamic_cast<TextComponent *>(component))->draw();
    // }
    //
    return true;
}

void GameObject::add_component(Component &component){
    Log::instance.info("Adding component: '" + component.component_id + "' to game object: '" + main_name + "'.");
    //Adiciona o componente no fim da lista referente ao tipo do mesmo.
    main_components[std::type_index(typeid(component))].push_back(&component);

}

Component* GameObject::get_component(std::string name){
    for(auto id_componentList: main_components){
        //Iterando a lista de componentes do tipo encontrado.
        for(auto component:id_componentList.second){
            if(component->component_id == name){
                return component;
            }
        }
    }
    Log::instance.warning("Component"+ name + " not found");
    return NULL;
}

void GameObject::setState(State state){
    main_state = state;
}
