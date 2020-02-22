
/* Created by Romain FOUYER on 23/11/2019 at 11:59. */


#include "systems/TimerSystem.hpp"
#include "worlds/WorldManager.hpp"
#include "components/Timer.hpp"

rtype::systems::TimerSystem::TimerSystem(const std::string &name)
: System(name)
{

}

void rtype::systems::TimerSystem::onInit()
{

}

void rtype::systems::TimerSystem::onUpdate(float elapsedTime)
{
    float elapsedTimeAsSecond = elapsedTime / 1000000000.0f;
    auto &worldManager = rtype::worlds::WorldManager::getInstance();
    std::vector<std::string> entitiesToDelete;

    worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Timer"}), [&entitiesToDelete, &worldManager, elapsedTimeAsSecond](ecs::entities::Entity *entity) {
        auto timer = dynamic_cast<rtype::components::Timer *>(entity->getComponent("Timer"));

        if (timer->getCurrentTime() > timer->getTimeToLive())
            entitiesToDelete.push_back(entity->getName());
        else
            timer->setCurrentTime(timer->getCurrentTime() + elapsedTimeAsSecond);
    });
    for (auto &entityToDelete : entitiesToDelete)
        worldManager.getCurrentWorld()->getEntityManager().deleteEntity(entityToDelete);
}

void rtype::systems::TimerSystem::onClose()
{
}