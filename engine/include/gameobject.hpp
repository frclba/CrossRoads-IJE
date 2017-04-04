#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "sdl2core.hpp"

// #include <boost/any.hpp>
// #include <boost/if.hpp>
// #include <unordered_map>
#include <utility>

namespace engine{

    class GameObject{
    public:
        // virtual ~GameObject();
        // void addComponent(boost::any &component, std::string component_name);
        // virtual void update(float timer) = 0;
        // std::vector components;
        // std::unordered_map <std::string, boost::any *> components_list;
        float position_x = 0;
        float position_y = 0;
        float height = 0;
        float width = 0;
    };

}

#endif
