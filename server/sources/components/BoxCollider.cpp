
/* Created by Romain FOUYER on 28/11/2019 at 10:27. */


#include "components/BoxCollider.hpp"

rtype::components::BoxCollider::BoxCollider(ecs::entities::Entity &entity, rtype::commons::Vector2<float> size)
: Component(entity), _size(size), _position(0, 0)
{
}

const rtype::commons::Vector2<float> &rtype::components::BoxCollider::getSize() const
{
    return _size;
}

void rtype::components::BoxCollider::setSize(rtype::commons::Vector2<float> newSize)
{
    _size = newSize;
}

const rtype::commons::Vector2<float> &rtype::components::BoxCollider::getPosition() const
{
    return _position;
}

void rtype::components::BoxCollider::setPosition(rtype::commons::Vector2<float> newPosition)
{
    _position = newPosition;
}