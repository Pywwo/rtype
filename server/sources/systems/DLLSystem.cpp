/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** DLLSystem.cpp
*/

/* Created the 28/11/2019 at 16:11 by jbulteau */

#include <stdexcept>
#include "systems/DLLSystem.hpp"

#include "dl/DLLoader.hpp"
#include "dl/DirectoryReader.hpp"

rtype::systems::DLLSystem::DLLSystem(const std::string &name, ecs::managers::SystemManager &systemManager, ecs::managers::EntityManager &entityManager)
    : System(name)
    , _systemManager(systemManager)
    , _entityManager(entityManager)
    , _dlLoader()
    , _systems()
{}

void rtype::systems::DLLSystem::onInit()
{
    std::vector<std::string> files = commons::DirectoryReader::fetchFilesFromDirectory("./lib");

    for (auto &file : files) {
        auto newSystem = _dlLoader.fetchFunctionFromLibrary<ecs::systems::System, ecs::managers::EntityManager &>("./lib/" + file, "createSystem", _entityManager);
        if (newSystem) {
            _systems.push_back(newSystem->getName());
            _systemManager.newSystem(newSystem->getName(), newSystem);
            _systemManager.startSystem(newSystem->getName());
        }
    }
}

void rtype::systems::DLLSystem::onUpdate([[maybe_unused]] float elapsedTime)
{
    for (auto &system : _systems) {
        try {
            if (_systemManager.getSystem(system)->getState() == ecs::systems::STOPPED) {
                _systemManager.startSystem(system);
            }
        } catch (std::out_of_range &) {}
    }

    std::vector<std::string> files = commons::DirectoryReader::fetchFilesFromDirectory("./lib");

    for (auto &file : files) {
        auto newSystem = _dlLoader.fetchFunctionFromLibrary<ecs::systems::System, ecs::managers::EntityManager &>("./lib/" + file, "createSystem", _entityManager);
        if (newSystem && std::find(_systems.begin(), _systems.end(), newSystem->getName()) == _systems.end()) {
            _systems.push_back(newSystem->getName());
            _systemManager.newSystem(newSystem->getName(), newSystem);
            _systemManager.startSystem(newSystem->getName());
        }
    }
}

void rtype::systems::DLLSystem::onClose()
{
    for (auto &system : _systems) {
        try {
            _systemManager.stopSystem(system);
        } catch (std::out_of_range &) {}
    }
}
