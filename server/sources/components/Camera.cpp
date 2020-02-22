/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Camera
*/

#include "components/Camera.hpp"

rtype::components::Camera::Camera(ecs::entities::Entity &entity)
    : Component(entity), _camera(std::make_pair(0, 0)), _center(0, 0), _size(0, 0), _zoom(1)
{

}

void rtype::components::Camera::setCenter(float x, float y)
{
    _center.x = x;
    _center.y = y;
    _camera.first = x;
    _camera.second = y;
}

const rtype::commons::Vector2<float> &rtype::components::Camera::getCenter() const
{
    return _center;
}

void rtype::components::Camera::setZoom(float newZoom)
{
    _zoom = newZoom;
}

float rtype::components::Camera::getZoom() const
{
    return _zoom;
}

void rtype::components::Camera::setSize(float x, float y)
{
    _size.x = x;
    _size.y = y;
}

const rtype::commons::Vector2<float> &rtype::components::Camera::getSize() const
{
    return _size;
}

void rtype::components::Camera::move(float offsetX, float offsetY)
{
    _center.x += offsetX;
    _center.y += offsetY;
    _camera.first += offsetX;
    _camera.second += offsetY;
}