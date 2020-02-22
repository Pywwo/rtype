/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** TimerSystem
*/

#include "Timer.hpp"

#include "../movement_system/MovementSystem.hpp"
#include "TimerSystem.hpp"

rtype::systems::TimerSystem::TimerSystem(const std::string &name, ecs::managers::EntityManager &entityManager)
    : System(name), _entityManager(entityManager)
{

}

void rtype::systems::TimerSystem::onInit()
{

}

void rtype::systems::TimerSystem::onUpdate(float elapsedTime)
{
    float elapsedTimeAsSecond = elapsedTime / 1000000000.0f;
    std::vector<std::string> entityToDelete;

    _entityManager.applyToEach(std::vector<std::string>({"Timer"}), [&entityToDelete, elapsedTimeAsSecond](ecs::entities::Entity *entity) {
        auto timer = dynamic_cast<rtype::components::Timer *>(entity->getComponent("Timer"));

        if (timer->getCurrentTime() > timer->getTimeToLive()) {
            entityToDelete.push_back(entity->getName());
        } else
            timer->setCurrentTime(timer->getCurrentTime() + elapsedTimeAsSecond);

    });
    for (auto &it : entityToDelete)
        _entityManager.deleteEntity(it);
}

void rtype::systems::TimerSystem::onClose()
{

}

extern "C"
{
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        __declspec(dllexport)
    #endif
    rtype::systems::TimerSystem *createSystem(ecs::managers::EntityManager &entityManager)
    {
        return new rtype::systems::TimerSystem("Timer system", entityManager);
    }
}