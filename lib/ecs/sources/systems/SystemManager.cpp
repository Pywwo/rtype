
/* Created by Romain FOUYER on 05/11/2019 at 10:41. */


#include <iostream>
#include "systems/SystemManager.hpp"

ecs::managers::SystemManager::SystemManager()
: _timeScale(1), _last(std::chrono::steady_clock::now()), _elapsedTime(0)
{
}

ecs::managers::SystemManager::~SystemManager()
{
    for (auto &it : _systems)
        delete it.second;
}

ecs::systems::System *ecs::managers::SystemManager::getSystem(const std::string &systemName)
{
    return _systems.at(systemName);
}

void ecs::managers::SystemManager::newSystem(const std::string &systemName, ecs::systems::System *newSystem)
{
    _systems.insert(_systems.end(), std::make_pair(systemName, newSystem));
}

void ecs::managers::SystemManager::startSystem(const std::string &systemName)
{
    _systems.at(systemName)->onInit();
    _systems.at(systemName)->setState(ecs::systems::STARTED);
}

void ecs::managers::SystemManager::stopSystem(const std::string &systemName)
{
    _systems.at(systemName)->onClose();
    _systems.at(systemName)->setState(ecs::systems::STOPPED);
}

void ecs::managers::SystemManager::runningTime()
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::nanoseconds elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>((now - _last) * _timeScale);

    _elapsedTime = elapsedTime.count();
    for (auto &it : _systems) {
        if (it.second->getState() == ecs::systems::STARTED)
            it.second->onUpdate(elapsedTime.count());
    }
    _last = now;
}

float ecs::managers::SystemManager::getTimeScale() const
{
    return _timeScale;
}

void ecs::managers::SystemManager::setTimeScale(float newTimeScale)
{
    _timeScale = newTimeScale;
}

float ecs::managers::SystemManager::getElapsedTime() const
{
    return _elapsedTime;
}
