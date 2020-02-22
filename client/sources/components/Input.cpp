
/* Created by Romain FOUYER on 20/11/2019 at 17:08. */


#include "Input.hpp"

#include "utilities/AssetsManager.hpp"

#include <iostream>

rtype::components::Input::Input(ecs::entities::Entity &entity)
: Component(entity), _playerInput(), _callback()
{
}

void rtype::components::Input::newInput(char c)
{
    _playerInput += c;
}

void rtype::components::Input::deleteLastCharacter()
{
    if (_playerInput.getSize()) {
        _playerInput.erase(_playerInput.getSize() - 1, _playerInput.getSize());
    }
}

void rtype::components::Input::setCallback(std::function<void(void)> callback)
{
    _callback = callback;
}

std::function<void(void)> &rtype::components::Input::getCallback()
{
    return _callback;
}

const sf::String& rtype::components::Input::getCurrentInput() const
{
    return _playerInput;
}