
/* Created by Romain FOUYER on 19/11/2019 at 11:57. */


#include "Button.hpp"

rtype::components::Button::Button(ecs::entities::Entity &entity, std::function<void(void)> callback)
: Component(entity), _callback(callback)
{}

std::function<void(void)> &rtype::components::Button::getCallback()
{
    return _callback;
}