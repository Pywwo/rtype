
/* Created by Romain FOUYER on 18/11/2019 at 19:19. */


#include "OpacityChanger.hpp"

rtype::components::OpacityChanger::OpacityChanger(ecs::entities::Entity &entity, float begin, float end, float speed)
: Component(entity), _begin(begin), _end(end), _speed(speed)
{
}

float rtype::components::OpacityChanger::getBegin() const
{
    return _begin;
}

float rtype::components::OpacityChanger::getEnd() const
{
    return _end;
}

float rtype::components::OpacityChanger::getSpeed() const
{
    return _speed;
}

void rtype::components::OpacityChanger::setBegin(float begin) {
    _begin = begin;
}

void rtype::components::OpacityChanger::setEnd(float end) {
    _end = end;
}

void rtype::components::OpacityChanger::setSpeed(float speed) {
    _speed = speed;
}
