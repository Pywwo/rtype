
/* Created by Romain FOUYER on 22/11/2019 at 09:58. */


#include "Camera.hpp"

rtype::components::Camera::Camera(ecs::entities::Entity &entity)
: Component(entity), _center(0, 0), _size(0, 0), _zoom(1)
{
}

rtype::components::Camera::Camera(ecs::entities::Entity &entity, rtype::commons::Vector2<float> center, float zoom)
: Component(entity), _center(center.x, center.y), _zoom(zoom)
{
    _camera.setCenter(_center.x, _center.y);
    _camera.zoom(_zoom);
}

void rtype::components::Camera::setCenter(float x, float y)
{
    _center.x = x;
    _center.y = y;
    _camera.setCenter(_center.x, _center.y);
}

const rtype::commons::Vector2<float> &rtype::components::Camera::getCenter() const
{
    return _center;
}

void rtype::components::Camera::setZoom(float newZoom)
{
    _zoom = newZoom;
    _camera.zoom(_zoom);
}

float rtype::components::Camera::getZoom() const
{
    return _zoom;
}

void rtype::components::Camera::setSize(float x, float y)
{
    _size.x = x;
    _size.y = y;
    _camera.setSize(x, y);
}

const rtype::commons::Vector2<float> &rtype::components::Camera::getSize() const
{
    return _size;
}

void rtype::components::Camera::move(float offsetX, float offsetY)
{
    _camera.move(offsetX, offsetY);
    _center.x += offsetX;
    _center.y += offsetY;
}

const sf::View &rtype::components::Camera::getCamera() const
{
    return _camera;
}