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
    Component(): _main_game_object(NULL), main_state(State::invalid){}

    Component(GameObject &gameObject, std::string name)
    : component_id(name), _main_game_object(&gameObject), main_state(State::enabled){}

    virtual ~Component() {};
    virtual bool init(){ return true; }
    virtual bool shutdown(){ return true; }

    inline State state(){ return main_state; }

    inline void enable() { main_state = State::enabled; }
    inline void disable() { main_state = State::disabled; }

    std::string component_id;

    State main_state;
    // State main_state;
  protected:
    //O componente guarda uma referência do game object ao qual pertence.
    GameObject* _main_game_object;


  };
}

#endif
