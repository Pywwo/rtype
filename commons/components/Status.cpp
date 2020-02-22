
/* Created by Romain FOUYER on 25/11/2019 at 10:25. */


#include "Status.hpp"

rtype::components::Status::Status(ecs::entities::Entity &entity)
: Component(entity), _isAlive(true)
{
}

bool rtype::components::Status::isAlive() const
{
    return _isAlive;
}

void rtype::components::Status::setAlive(bool alive)
{
    _isAlive = alive;
}