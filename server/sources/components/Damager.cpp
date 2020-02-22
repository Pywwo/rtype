
/* Created by Romain FOUYER on 28/11/2019 at 10:43. */


#include "components/Damager.hpp"

rtype::components::Damager::Damager(ecs::entities::Entity &entity, ecs::entities::Entity &damagerEntity, bool shouldDestroyOnCollide)
: Component(entity), _damagerEntity(damagerEntity), _shouldDestroyOnCollide(shouldDestroyOnCollide)
{
}

void rtype::components::Damager::setDamagerEntity(ecs::entities::Entity &newDamagerEntity)
{
    _damagerEntity = newDamagerEntity;
}

const ecs::entities::Entity& rtype::components::Damager::getDamagerEntity() const
{
    return _damagerEntity;
}

bool rtype::components::Damager::shouldDestroyOnCollide() const
{
    return _shouldDestroyOnCollide;
}

void rtype::components::Damager::setShouldDestroyOnCollide(bool shouldDestroy)
{
    _shouldDestroyOnCollide = shouldDestroy;
}