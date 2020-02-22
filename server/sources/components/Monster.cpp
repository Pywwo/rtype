/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Monster
*/

#include "components/Monster.hpp"

rtype::components::Monster::Monster(ecs::entities::Entity &entity, const Enemy &enemyId)
    : Component(entity), _enemyId(enemyId), _isSpawn(false)
{
}

rtype::Enemy rtype::components::Monster::getId()
{
    return _enemyId;
}

void rtype::components::Monster::setId(const Enemy &enemyId)
{
    _enemyId = enemyId;
}

bool rtype::components::Monster::isSpawned() const
{
    return _isSpawn;
}

void rtype::components::Monster::setSpawnState(const bool &state)
{
    _isSpawn = state;
}