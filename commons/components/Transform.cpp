
/* Created by Romain FOUYER on 18/11/2019 at 18:03. */


#include "Transform.hpp"

rtype::components::Transform::Transform(ecs::entities::Entity &entity)
: Component(entity), _position(0, 0), _scale(1, 1)
{
}

void rtype::components::Transform::setPosition(float x, float y)
{
    _position.x = x;
    _position.y = y;
}

rtype::commons::Vector2<float> rtype::components::Transform::getPosition() const
{
    return _position;
}

void rtype::components::Transform::setRotation(float x, float y)
{
    _rotation.x = x;
    _rotation.y = y;
}

rtype::commons::Vector2<float> rtype::components::Transform::getRotation() const
{
    return _rotation;
}

void rtype::components::Transform::setScale(float x, float y)
{
    _scale.x = x;
    _scale.y = y;
}

rtype::commons::Vector2<float> rtype::components::Transform::getScale() const
{
    return _scale;
}