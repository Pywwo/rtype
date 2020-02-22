
/* Created by Romain FOUYER on 20/11/2019 at 21:20. */


#include "Controller.hpp"

rtype::components::Controller::Controller(ecs::entities::Entity &entity, float speed)
: Component(entity), _speed(speed)
{
}

float rtype::components::Controller::getSpeed() const {
    return _speed;
}

void rtype::components::Controller::setSpeed(float speed) {
    _speed = speed;
}

const rtype::commons::Vector2<float> &rtype::components::Controller::getVelocity() const
{
    return _velocity;
}

void rtype::components::Controller::setVelocity(const rtype::commons::Vector2<float> &velocity)
{
    _velocity = velocity;
}
