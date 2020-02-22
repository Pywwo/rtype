
/* Created by Romain FOUYER on 05/11/2019 at 10:49. */


#include "entities/EntityManager.hpp"

#include <vector>
#include <algorithm>
#include <string>

ecs::managers::EntityManager::EntityManager()
: _maxId(0)
{}

ecs::managers::EntityManager::~EntityManager()
{
    for (auto &it : _entities)
        delete it.second;
}

void ecs::managers::EntityManager::applyToEach(std::vector<std::string> components, typename std::common_type<std::function<void(entities::Entity *)>>::type func)
{
    for (auto &entity : _entities) {
        if (entity.second->hasComponents(components) && entity.second->isEnabled()) {
            func(entity.second);
        }
    }
}

ecs::entities::Entity *ecs::managers::EntityManager::getEntityById(int id)
{
    return _entities.at(id);
}

ecs::entities::Entity *ecs::managers::EntityManager::getEntityByName(const std::string &name)
{
    for (auto &it : _entities) {
        if (it.second->getName() == name)
            return it.second;
    }
    return nullptr;
}

std::vector<ecs::entities::Entity *> ecs::managers::EntityManager::getEntitiesByName(const std::string &name)
{
    std::vector<ecs::entities::Entity *> fetchEntities;

    for (auto &it : _entities)
        if (it.second->getName() == name)
            fetchEntities.push_back(it.second);

    return fetchEntities;
}

void ecs::managers::EntityManager::createEntity(const std::string &name)
{
    auto *newEntity = new ecs::entities::Entity(_maxId, name);

    _entities.insert(std::make_pair(_maxId, newEntity));
    _maxId++;
}

void ecs::managers::EntityManager::deleteEntity(const std::string &name)
{
    int entityId = -1;

    for (auto &entity : _entities) {
        if (entity.second->getName() == name)
            entityId = entity.first;
    }
    if (entityId != -1) {
        for (auto &component : _entities.at(entityId)->getAllComponents()) {
            delete component.second;
        }
        _entities.erase(entityId);
    }
}

std::vector<ecs::entities::Entity *> ecs::managers::EntityManager::getEntitiesWithComponents(std::vector<std::string> components)
{
    std::vector<ecs::entities::Entity *> entities;

    for (auto &entity : _entities) {
        if (entity.second->hasComponents(components) && entity.second->isEnabled()) {
            entities.push_back(entity.second);
        }
    }
    return entities;
}

void ecs::managers::EntityManager::deleteAllEntities()
{
    std::vector<std::string> toDelete;

    for (auto &it : _entities)
        toDelete.push_back(it.second->getName());
    for (auto &delName : toDelete)
        deleteEntity(delName);
}