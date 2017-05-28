#include "gameobject.hpp"
#include "components/image.hpp"
#include "components/animation.hpp"


using namespace engine;

bool GameObject::init()
{
  //    INFO("Init game object " << m_name);

    for(auto id_componentlist: main_components)
    {
        for (auto component: id_componentlist.second)
        {
            if(component->init() == false) return false;
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
    Log::instance.info("Adding components to game object");
    //Adiciona o componente no fim da lista referente ao tipo do mesmo.
    main_components[std::type_index(typeid(component))].push_back(&component);

}

void GameObject::update()
{
    for(auto id_componentlist: main_components)
    {
        for (auto component: id_componentlist.second)
        {
	  if(component->state() == Component::State::enabled){
                component->update();
	  }
        }
    }
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

// template<typename T>std::list<Component *> GameObject::get_components(){
//     return main_components[std::type_index(typeid(T))];
// }

void GameObject::setState(State state){
    main_state = state;
}

/*bool GameObject::collision(GameObject* object){
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
}*/

//GameObject* GameObject::checkCollision(){
// Game::instance.current_scene->

//}
