
/* Created by Romain FOUYER on 05/11/2019 at 10:14. */


#include "components/Component.hpp"

ecs::components::Component::Component(ecs::entities::Entity &entity)
: _entity(entity)
{
}

ecs::entities::IEntity &ecs::components::Component::getEntity()
{
    return _entity;
}
