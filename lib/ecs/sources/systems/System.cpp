
/* Created by Romain FOUYER on 05/11/2019 at 10:33. */


#include "systems/System.hpp"

ecs::systems::System::System(const std::string &name)
: _name(name), _state(STOPPED)
{
}

const std::string &ecs::systems::System::getName() const
{
    return _name;
}

ecs::systems::SystemState ecs::systems::System::getState() const
{
    return _state;
}

void ecs::systems::System::setState(ecs::systems::SystemState newState)
{
    _state = newState;
}