
/* Created by Romain FOUYER on 06/11/2019 at 13:33. */


#include "worlds/World.hpp"

rtype::worlds::World::World(const std::string &name)
: _worldName(name), _entityManager()
{
}

ecs::managers::EntityManager &rtype::worlds::World::getEntityManager()
{
    return _entityManager;
}

const std::string &rtype::worlds::World::getWorldName() const
{
    return _worldName;
}