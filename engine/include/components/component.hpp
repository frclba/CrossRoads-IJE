#ifndef _ENGINE_COMPONENTS_COMPONENT
#define _ENGINE_COMPONENTS_COMPONENT

namespace engine{
  //Define a class gameobject como vazia aqui, para não ter problemas de importação cíclica.
  class GameObject;

  class Component{
  public:
    enum class State{
      enabled,
      disabled,
      invalid
    };

    //Sobrecarga do construtor para  componentes criados sem parâmetros serem invalidados.
    Component(): main_state(State::invalid), _main_game_object(NULL){}

    Component(GameObject &gameObject, std::string name)
    : component_id(name), main_state(State::enabled), _main_game_object(&gameObject){}

    virtual ~Component() {};
    virtual bool init(){ return true; }
    virtual bool shutdown(){ return true; }

    inline State state(){ return main_state; }

    std::string component_id;

    State main_state;
    // State main_state;
  protected:
    //O componente guarda uma referência do game object ao qual pertence.
    GameObject* _main_game_object;
  };
}

#endif
