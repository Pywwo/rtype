
/* Created by Romain FOUYER on 24/11/2019 at 15:33. */


#include "Event.hpp"

rtype::components::Event::Event(ecs::entities::Entity &entity)
: Component(entity)
{
}

void rtype::components::Event::addEvent(const std::string &name, std::function<void(void)> callback)
{
    _callbacks.insert(std::make_pair(name, callback));
}

std::function<void(void)> rtype::components::Event::getSpecificCallback(const std::string &name)
{
    return _callbacks.at(name);
}