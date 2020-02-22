
/* Created by Romain FOUYER on 19/11/2019 at 09:55. */


#include "Rectangle.hpp"

rtype::components::Rectangle::Rectangle(ecs::entities::Entity &entity, int left, int top, int width, int height)
: Component(entity), _left(left), _top(top), _width(width), _height(height) {}

int rtype::components::Rectangle::getLeft() const {
    return _left;
}

int rtype::components::Rectangle::getTop() const {
    return _top;
}

int rtype::components::Rectangle::getWidth() const {
    return _width;
}

int rtype::components::Rectangle::getHeight() const {
    return _height;
}

void rtype::components::Rectangle::setLeft(int left) {
    _left = left;
}

void rtype::components::Rectangle::setTop(int top) {
    _top = top;
}

void rtype::components::Rectangle::setWidth(int width) {
    _width = width;
}

void rtype::components::Rectangle::setHeight(int height) {
    _height = height;
}
