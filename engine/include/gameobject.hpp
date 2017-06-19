#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <unordered_map>
#include <utility>
#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>

#include "sdl2core.hpp"
#include "components/component.hpp"

namespace engine{

  class GameObject{
  public:
    enum class Layer{
      background,
      layer1,
      layer2,
      layer3
    };
    enum class State{
      enabled,
      disabled,
      invalid
    };
    //Sobrecarga do construtor, para caso seja criado um gameobject sem parâmetros, ele ser tratado com inválido.
    GameObject(): GameObject("",false,"",State::invalid){}

    //Constructor
    GameObject(std::string name,bool collision = false,std::string m_type = "", State state=State::enabled)
    : main_positionX(0), main_positionY(0), main_width(0), main_height(0), main_rotation(0),m_collision(collision),
    type(m_type), m_layer(Layer::layer2), main_state(state), main_name(name){}

    virtual ~GameObject(){};

    //Init on each component on a map of components, then for each element in a list of components
    virtual bool init();

    //Shutdown on each component
    virtual bool shutdown();

    //Search, does a type cast and draw on screen a component, if its state is enabled
    virtual bool draw();

    void update();
    //Add the component on the end of a list of its type.
    void add_component(Component &component);

    void setState(State state);

    bool checkCollision(GameObject* object);

    //funcao que busca um component a partir do seu id.
    Component* get_component(std::string name);

    // template<typename T> T *get_component(){
    //     return dynamic_cast<T *>(main_components[std::type_index(typeid(T))].front());
    // }

    // template<typename T> std::list<Component *> get_components();

    inline std::string name() const {
        return main_name;
    }

    inline State state() const {
        return main_state;
    }

    inline void set_size(int width, int height) {
        main_width = width;
        main_height = height;
    }

    inline void set_layer(Layer layer) {
        m_layer = layer;
    }

    int main_positionX, main_positionY;
    int main_width, main_height;
    int main_rotation;
    bool m_collision;

    std::string type;

    Layer m_layer;

  private:
    State main_state;
    std::string main_name;

    /*Mapa não ordenado que vai armazenar todos os componentes do game object. A chave será definida pelo
    tipo do componente, e o valor será uma lista de componentes daquele tipo (Sprites,audios,etc)*/
    std::unordered_map <std::type_index, std::list<Component *> > main_components;
  };

}

#endif
