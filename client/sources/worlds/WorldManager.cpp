
/* Created by Romain FOUYER on 06/11/2019 at 13:41. */


#include "worlds/WorldManager.hpp"

rtype::worlds::WorldManager &rtype::worlds::WorldManager::getInstance()
{
    static rtype::worlds::WorldManager wm;

    return wm;
}

rtype::worlds::WorldManager::~WorldManager()
{
    for (auto &it : _worlds) {
        delete it.second;
    }
}

void rtype::worlds::WorldManager::addWorld(rtype::worlds::World *world)
{
    _worlds[world->getWorldName()] = world;
}

rtype::worlds::World *rtype::worlds::WorldManager::getCurrentWorld()
{
    return _worlds.at(currentWorldName);
}

rtype::worlds::World *rtype::worlds::WorldManager::getWorldByName(const std::string &worldName)
{
    return _worlds.at(worldName);
}

void rtype::worlds::WorldManager::changeWorld(const std::string &worldName)
{
    currentWorldName = worldName;
}