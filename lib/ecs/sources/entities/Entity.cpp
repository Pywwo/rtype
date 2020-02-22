
/* Created by Romain FOUYER on 05/11/2019 at 10:15. */

#include "entities/Entity.hpp"

ecs::entities::Entity::Entity(unsigned int id, const std::string &name)
: _id(id), _name(name), _enable(true)
{
}

ecs::entities::Entity::~Entity()
{
    for (auto &it : _components)
        delete it.second;
}

void ecs::entities::Entity::assignComponent(const std::string &componentName, ecs::components::IComponent *newComponent)
{
    _components[componentName] = newComponent;
}

void ecs::entities::Entity::removeComponent(const std::string &componentName)
{
    for (auto &it : _components) {
        if (it.first == componentName) {
            _components.erase(it.first);
        }
    }
}

ecs::components::IComponent *ecs::entities::Entity::getComponent(const std::string &componentName)
{
    return _components.at(componentName);
}

std::vector<ecs::components::IComponent *> ecs::entities::Entity::getComponents(std::vector<std::string> componentsName)
{
    std::vector<ecs::components::IComponent *> components;

    for (auto &component : _components) {
        for (auto &it : componentsName) {
            if (it == component.first)
                components.push_back(component.second);
        }
    }
    return components;
}

bool ecs::entities::Entity::hasComponent(const std::string &component) const
{
    for (auto &it : _components)
        if (it.first == component)
            return true;
    return false;
}

bool ecs::entities::Entity::hasComponents(std::vector<std::string> components) const
{
    for (auto &componentName : components) {
        if (hasComponent(componentName)) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

const unsigned int &ecs::entities::Entity::getId() const
{
    return _id;
}

const std::string &ecs::entities::Entity::getName() const
{
    return _name;
}

const std::unordered_map<std::string, ecs::components::IComponent *> &ecs::entities::Entity::getAllComponents() const
{
    return _components;
}

void ecs::entities::Entity::enable()
{
    _enable = true;
}

void ecs::entities::Entity::disable()
{
    _enable = false;
}

bool ecs::entities::Entity::isEnabled() const
{
    return _enable;
}