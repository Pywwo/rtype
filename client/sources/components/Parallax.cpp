
/* Created by Romain FOUYER on 22/11/2019 at 11:08. */


#include "Parallax.hpp"

rtype::components::Parallax::Parallax(ecs::entities::Entity &entity, float speed)
: Component(entity), _speed(speed)
{}

float rtype::components::Parallax::getSpeed() const
{
    return _speed;
}

void rtype::components::Parallax::setSpeed(float newSpeed)
{
    _speed = newSpeed;
}